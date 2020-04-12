#define MAX_DATA_SIZE 11
#define MAX_NEIGHBOUR_GROUPS_SIZE 17
#define MAX_MESSAGE_SEGMENTS 128

#define RADIO_ENQUIRE_PACKET 0
#define RADIO_RESPONSE_PACKET 1
#define RADIO_DATA_PACKET 2

/**
 * Packet Format:
 *      Type 1 -- Enquire Packet:
 *          type(1byte->1char->int) source(2bytes->2char->2digit int)
 *      Type 2 -- Response Packet:
 *          type(1byte->1char->int) source(2bytes->2char->2digit int) groupNeighbours(17bytes->array of 17 1char ints ie. 1, 2, .., 9)
 *      Type 3 -- Data Packet:
 *          type(1byte->1char->int) source(2bytes->2char->2digit int) groupId(1char->int) id(2bytes->2char->2digit int) sequenceNumber(2bytes->2char->2digit int) lastPacket(1byte->1char->bool) data(11bytes->11char array)
 **/

class ChirpRadioPacket
{
    public:
        ChirpRadioPacket();
        ChirpRadioPacket(char[]);
        int getPacketType();
        void setPacketType(int);
        int getSourceId();
        void setSourceId(int);
        int getGroupId();
        void setGroupId(int);
        int getId();
        void setId(int);
        int getSequenceNumber();
        void setSequenceNumber(int);
        bool isLastPacket();
        void setLastPacket(bool);
        char* getData();
        void setData(char[]);
        int* getNeighbourGroups();
        void setNeighbourGroups(int[]);
        char* serialize();
    private:
        int packetType;
        int sourceId;
        int groupId;
        int id;
        int sequenceNumber;
        bool lastPacket;
        char data[MAX_DATA_SIZE];
        int neighbourGroups[MAX_NEIGHBOUR_GROUPS_SIZE];
        int neighbourGroupsSize;
};
