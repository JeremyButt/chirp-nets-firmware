#include "ChirpRadioPacket.h"
#include "utils.h"
#include <string>

/*CLASS METHODS*/
ChirpRadioPacket::ChirpRadioPacket()
{
}

ChirpRadioPacket::ChirpRadioPacket(char packet[])
{
    this->packetType = parse_int(packet[0]);

    char source[] = {packet[1], packet[2]};
    this->sourceId = parse_2digit_int(source);

    if(this->packetType == RADIO_ENQUIRE_PACKET)
    {
    }
    else if(this->packetType == RADIO_RESPONSE_PACKET)
    {
        int i = 3;
        int position = 0;
        while(position < MAX_NEIGHBOUR_GROUPS_SIZE)
        {
            this->neighbourGroups[position] = parse_int(packet[i]);
            i++;
            position++;
        }
        this->neighbourGroupsSize = position;
    }
    else if(this->packetType == RADIO_DATA_PACKET)
    {
        this->groupId = parse_int(packet[3]);
        char id[] = {packet[4], packet[5]};
        this->id = parse_2digit_int(id);
        char sequence_number[] = {packet[6], packet[7]};
        this->sequenceNumber = parse_2digit_int(sequence_number);
        this->lastPacket = parse_bool(packet[8]);
        int i = 9;
        int position = 0;
        while(position < MAX_DATA_SIZE)
        {
            this->data[position] = packet[i];
            i++;
            position++;
        }
    } 
    else
    {
        throw "ERROR: This is NOT a Valid Packet Type!";
    }
}

int ChirpRadioPacket::getPacketType()
{
    return this->packetType;
}

void ChirpRadioPacket::setPacketType(int packetType)
{
    this->packetType = packetType;
}

int ChirpRadioPacket::getSourceId()
{
    return this->sourceId;
}

void ChirpRadioPacket::setSourceId(int sourceId)
{
    this->sourceId = sourceId;
}

int ChirpRadioPacket::getGroupId()
{
    if(this->packetType == RADIO_DATA_PACKET)
    {
        return this->groupId;
    }
}

void ChirpRadioPacket::setGroupId(int groupId)
{
    if(this->packetType == RADIO_DATA_PACKET)
    {
        this->groupId = groupId;
    }
}

int ChirpRadioPacket::getId()
{
    if(this->packetType == RADIO_DATA_PACKET)
    {
        return this->id;
    }
    return USHRT_MAX;
}

void ChirpRadioPacket::setId(int id)
{
    if(this->packetType == RADIO_DATA_PACKET)
    {
        this->id = id;
    }
}

int ChirpRadioPacket::getSequenceNumber()
{
    if(this->packetType == RADIO_DATA_PACKET)
    {
        return this->sequenceNumber;
    }
}

void ChirpRadioPacket::setSequenceNumber(int sequenceNumber)
{
    if(this->packetType == RADIO_DATA_PACKET)
    {
        this->sequenceNumber = sequenceNumber;
    }
}

bool ChirpRadioPacket::isLastPacket()
{
    if(this->packetType == RADIO_DATA_PACKET)
    {
        return this->lastPacket;
    }
    return false;
}

void ChirpRadioPacket::setLastPacket(bool lastPacket)
{
    if(this->packetType == RADIO_DATA_PACKET)
    {
        this->lastPacket = lastPacket;
    }
}

char* ChirpRadioPacket::getData()
{
    if(this->packetType == RADIO_DATA_PACKET)
    {
        return this->data;
    }
    return nullptr;
}

void ChirpRadioPacket::setData(char data[])
{
    if(this->packetType == RADIO_DATA_PACKET)
    {
        for(int i = 0; i < MAX_DATA_SIZE; i++)
        {
            this->data[i] = data[i];
        }
    }
}

int* ChirpRadioPacket::getNeighbourGroups()
{
    if(this->packetType == RADIO_RESPONSE_PACKET)
    {
        return this->neighbourGroups;
    }
    return nullptr;
}

void ChirpRadioPacket::setNeighbourGroups(int neighbourGroups[])
{
    if(this->packetType == RADIO_RESPONSE_PACKET)
    {
        for(int i = 0; i < MAX_NEIGHBOUR_GROUPS_SIZE; i++)
        {
            this->neighbourGroups[i] = neighbourGroups[i];
        }
    }
}

char* ChirpRadioPacket::serialize()
{
    if(this->packetType == RADIO_ENQUIRE_PACKET)
    {
        char* packet = new char[3];
        packet[0] = serialize_int(this->packetType)[0];
        char* sourceId = serialize_2digit_int(this->sourceId);
        packet[1] = sourceId[0];
        packet[2] = sourceId[1];
        return packet;
    }
    else if(this->packetType == RADIO_RESPONSE_PACKET)
    {
       char* packet = new char[20];
        packet[0] = serialize_int(this->packetType)[0];
        char* sourceId = serialize_2digit_int(this->sourceId);
        packet[1] = sourceId[0];
        packet[2] = sourceId[1];
        strcat(packet, serialize_int_array(this->neighbourGroups, MAX_NEIGHBOUR_GROUPS_SIZE));
        int i = 3;
        int position = 0;
        while(position < MAX_DATA_SIZE)
        {
            if(position < this->neighbourGroupsSize)
            {
                packet[i] = this->neighbourGroups[position];
            }
            else
            {
                packet[i] = NULL;
            }
            i++;
            position++;
        }
        return packet;
    }
    else if(this->packetType == RADIO_DATA_PACKET)
    {
        char* packet = new char[20];
        packet[0] = serialize_int(this->packetType)[0];
        char* sourceId = serialize_2digit_int(this->sourceId);
        packet[1] = sourceId[0];
        packet[2] = sourceId[1];
        packet[3] = serialize_int(this->groupId)[0];        
        char* id = serialize_2digit_int(this->id);
        packet[4] = id[0];
        packet[5] = id[1];
        char* sequenceNumber = serialize_2digit_int(this->sequenceNumber);
        packet[6] = sequenceNumber[0];
        packet[7] = sequenceNumber[1];
        packet[8] = serialize_bool(this->lastPacket)[0];
        int i = 9;
        int position = 0;
        int len = strlen(this->data);
        while(position < MAX_DATA_SIZE)
        {
            if(position < len)
            {
                packet[i] = this->data[position];
            }
            else
            {
                packet[i] = NULL;
            }
            i++;
            position++;
        }
        return packet;
    }
}
