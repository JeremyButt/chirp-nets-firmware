#include<string>
#include <math.h>

#include "ChirpFMRxTx.h"
#include "ChirpRouting.h"

ChirpRouter::ChirpRouter()
{
    this->messageId = 1;
    this->historyCacheSize = 0;
    this->messageSegmentCacheSize = 0;
}

void ChirpRouter::init(ChirpFMRxTx* radio)
{
    this->radio = radio;
}

void ChirpRouter::send(char payload[], size_t size)
{
    ChirpBluetoothPacket bluetooth_packet = ChirpBluetoothPacket(payload, size);
    if(bluetooth_packet.isInitPacket())
    {
        this->groupId = bluetooth_packet.getGroupId();
        this->nodeId = bluetooth_packet.getNodeId();
        this->radio->setGroupId(this->groupId);
        this->radio->setNodeId(this->nodeId);
    }
    else
    {
        for(int i = 0; i < ceil((float)size/MAX_DATA_SIZE); i++)
        {
            ChirpRadioPacket radio_packet = ChirpRadioPacket();
            radio_packet.setPacketType(RADIO_DATA_PACKET);
            radio_packet.setSourceId(this->nodeId);
            radio_packet.setGroupId(this->groupId);
            radio_packet.setId(messageId);
            radio_packet.setSequenceNumber(i);
            radio_packet.setLastPacket((i == ceil((float)size/MAX_DATA_SIZE)-1));
            char data[MAX_DATA_SIZE];
            int data_size = strlen(bluetooth_packet.getData());
            int pos = 0;
            for(int j = i*(MAX_DATA_SIZE-1); j < ((i*(MAX_DATA_SIZE-1))+MAX_DATA_SIZE-1); j++)
            {
                if(pos < data_size-1)
                {
                    data[pos] = bluetooth_packet.getData()[j];
                }
                else
                {
                    data[pos] = NULL;
                }
                pos++;
            }
            data[pos] = NULL;
            radio_packet.setData(data);
            this->radio->send(BROADCAST_ADDR, radio_packet.serialize(), 20);
        }
        this->messageId++;
    }
}

char* ChirpRouter::receive()
{
    char* received_data = radio->receive();
    if(received_data != NULL)
    {
        ChirpRadioPacket radio_packet = ChirpRadioPacket(received_data);
        if(!aleadyReceived(radio_packet) && radio_packet.getSourceId() != this->nodeId)
        {
            addToHistoryCache(radio_packet);
            historyCacheMaintenance();
            this->radio->send(BROADCAST_ADDR, received_data, 20);
            if(radio_packet.getGroupId() == this->radio->getGroupId())
            {
                if(radio_packet.isLastPacket() && radio_packet.getSequenceNumber() == 0)
                {
                    ChirpBluetoothPacket bluetooth_packet = ChirpBluetoothPacket();
                    bluetooth_packet.setPacketType(BLUETOOTH_DATA_PACKET);
                    bluetooth_packet.setGroupId(radio_packet.getGroupId());
                    bluetooth_packet.setNodeId(radio_packet.getSourceId());
                    bluetooth_packet.setData(radio_packet.getData());
                    return bluetooth_packet.serialize();
                }
                else
                {
                    this->addToMessageSegmentCache(radio_packet);
                    ChirpBluetoothPacket* bluetooth_packet = getMessageFromCache(radio_packet);
                    if(bluetooth_packet != nullptr)
                    {
                        return bluetooth_packet->serialize();
                    }
                }
            }
            else
            {
                return nullptr;
            }
        }
    }
    return nullptr;
}

void ChirpRouter::neighborNodeDiscovery()
{

}

void ChirpRouter::messageSegmentCacheMaintenance()
{
    struct MessageSegmentCacheEntry curr;
    for(int i = 0; i < this->messageSegmentCacheSize; i++)
    {
        curr = this->messageSegmentsCache[i];
        if((time(0) - curr.time_stamp >= MAX_MESSAGE_SEGMENTS_CACHE_TIMEOUT))
        {
            for(int j=i; j<(this->messageSegmentCacheSize-1); j++)
			{
				this->messageSegmentsCache[j] = this->messageSegmentsCache[j+1];
			}
            this->messageSegmentCacheSize--;
        }
    }
}

void ChirpRouter::historyCacheMaintenance()
{
    struct HistoryEntry curr;
    for(int i = 0; i < this->historyCacheSize; i++)
    {
        curr = this->history[i];
        if((time(0) - curr.time_stamp >= MAX_HISTORY_CACHE_TIMEOUT))
        {
            for(int j=i; j<(this->historyCacheSize-1); j++)
			{
				this->history[j] = this->history[j+1];
			}
            this->historyCacheSize--;
        }
    }
}

void ChirpRouter::addToMessageSegmentCache(ChirpRadioPacket packet)
{
    struct MessageSegmentCacheEntry curr;
    for(int i = 0; i < this->messageSegmentCacheSize; i++)
    {
        curr = this->messageSegmentsCache[i];
        if(curr.message_segment.getSourceId() == packet.getSourceId() && curr.message_segment.getGroupId() == packet.getGroupId() && curr.message_segment.getId() == packet.getId() && curr.message_segment.getSequenceNumber() == packet.getSequenceNumber())
        {
            return;
        }
    }

    time_t now = time(0);
    this->messageSegmentsCache[this->messageSegmentCacheSize++] = {now, packet};
}

void ChirpRouter::addToHistoryCache(ChirpRadioPacket packet)
{
    time_t now = time(0);
    this->history[this->historyCacheSize++] = {now, packet.getSourceId(), packet.getId(), packet.getGroupId(), packet.getSequenceNumber()};
}

bool ChirpRouter::aleadyReceived(ChirpRadioPacket packet)
{
    struct HistoryEntry curr;
    for(int i = 0; i < this->historyCacheSize; i++)
    {
        curr = this->history[i];        
        if(curr.source_id == packet.getSourceId() && curr.group_id == packet.getGroupId() && curr.packet_id == packet.getId() && curr.sequence_number == packet.getSequenceNumber())
        {
            return true;
        }
    }
    return false;
}

ChirpBluetoothPacket* ChirpRouter::getMessageFromCache(ChirpRadioPacket packet)
{
    ChirpBluetoothPacket* bluetooth_packet = new ChirpBluetoothPacket();
    bluetooth_packet->setPacketType(BLUETOOTH_DATA_PACKET);
    bluetooth_packet->setNodeId(packet.getSourceId());
    bluetooth_packet->setGroupId(packet.getGroupId());
    char data[MAX_BLUETOOTH_DATA_SIZE];
    int data_index = 0;

    struct MessageSegmentCacheEntry curr;
    int max_seq_num = 0;
    int count = 0;
    for(int i = 0; i < this->messageSegmentCacheSize; i++)
    {
        curr = this->messageSegmentsCache[i];
        if(curr.message_segment.getSourceId() == packet.getSourceId() && curr.message_segment.getGroupId() == packet.getGroupId() && curr.message_segment.getId() == packet.getId())
        {
            if(curr.message_segment.isLastPacket())
            {
                max_seq_num = curr.message_segment.getSequenceNumber();
            }
            count++;
        }
    }
    if(max_seq_num == 0 || max_seq_num+1 > count)
    {
        return nullptr;
    }

    for(int i = 0; i < max_seq_num+1; i++)
    {
        struct MessageSegmentCacheEntry curr;
        for(int j = 0; j < this->messageSegmentCacheSize; j++)
        {
            curr = this->messageSegmentsCache[j];
            if(curr.message_segment.getSourceId() == packet.getSourceId() && curr.message_segment.getGroupId() == packet.getGroupId() && curr.message_segment.getId() == packet.getId() && curr.message_segment.getSequenceNumber() == i)
            {
                for(int k = 0; k < strlen(curr.message_segment.getData()); k++)
                {
                    data[data_index++] = curr.message_segment.getData()[k];
                }
            }
        }
    }
    for(int i = 0; i < this->messageSegmentCacheSize; i++)
    {
        curr = this->messageSegmentsCache[i];
        if(curr.message_segment.getSourceId() == packet.getSourceId() && curr.message_segment.getGroupId() == packet.getGroupId() && curr.message_segment.getId() == packet.getId())
        {
            for(int j=i; j<(this->messageSegmentCacheSize-1); j++)
			{
				this->messageSegmentsCache[j] = this->messageSegmentsCache[j+1];
			}
        }
    }
    this->messageSegmentCacheSize = this->messageSegmentCacheSize - count;
    bluetooth_packet->setData(data);

    return bluetooth_packet;
}
