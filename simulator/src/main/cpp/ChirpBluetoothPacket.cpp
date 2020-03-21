#include "ChirpBluetoothPacket.h"
#include "utils.h"
#include <string>

ChirpBluetoothPacket::ChirpBluetoothPacket()
{
}

ChirpBluetoothPacket::ChirpBluetoothPacket(char packet[], size_t size)
{
    this->packetType = parse_int(packet[0]);
    this->groupId = parse_int(packet[1]);
    
    char node_id[] = {packet[2], packet[3]};
    this->nodeId = parse_2digit_int(node_id);

    if(this->packetType == BLUETOOTH_DATA_PACKET)
    {
        int i = 4;
        int position = 0;
        while(position < MAX_BLUETOOTH_DATA_SIZE)
        {
            if(i<size)
            {
                this->data[position] = packet[i];
            }
            else
            {
                this->data[position] = NULL;
            }
            i++;
            position++;
        }
    }
}

int ChirpBluetoothPacket::getPacketType()
{
    return this->packetType;
}

void ChirpBluetoothPacket::setPacketType(int packetType)
{
    this->packetType = packetType;
}

bool ChirpBluetoothPacket::isInitPacket()
{
    return (this->packetType == BLUETOOTH_INIT_PACKET);
}

int ChirpBluetoothPacket::getGroupId()
{
    return this->groupId;
}

void ChirpBluetoothPacket::setGroupId(int groupId)
{
    this->groupId = groupId;
}

int ChirpBluetoothPacket::getNodeId()
{
    return this->nodeId;
}

void ChirpBluetoothPacket::setNodeId(int nodeId)
{
    this->nodeId = nodeId;
}

char* ChirpBluetoothPacket::getData()
{
    if(this->packetType == BLUETOOTH_DATA_PACKET)
    {
        return this->data;
    }
    return nullptr;
}

void ChirpBluetoothPacket::setData(char* data)
{
    if(this->packetType == BLUETOOTH_DATA_PACKET)
    {
        int i = 0;
        while(i < MAX_BLUETOOTH_DATA_SIZE)
        {
            this->data[i] = data[i];
            i++;
        }
    }
}

char* ChirpBluetoothPacket::serialize()
{
    char* packet = new char[128];
    packet[0] = serialize_int(this->packetType)[0];
    packet[1] = serialize_int(this->groupId)[0];
    char* nodeId = serialize_2digit_int(this->nodeId);
    packet[2] = nodeId[0];
    packet[3] = nodeId[1];
    int i = 4;
    int position = 0;
    while(position < MAX_BLUETOOTH_DATA_SIZE)
    {
        packet[i] = this->data[position];
        i++;
        position++;
    }
    return packet;
}
