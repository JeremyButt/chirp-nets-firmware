#include <SPI.h>                // Included with Arduino IDE, should also add https://github.com/LowPowerLab/SPIFlash
#define BLUETOOTH_INIT_PACKET 2
#define BLUETOOTH_DATA_PACKET 1

#define MAX_BLUETOOTH_DATA_SIZE 123
#define MAX_BLUETOOTH_PACKET_SIZE 128

/**
 * Bluetooth Packet Format:
 *      Type 1 -- Init Packet:
 *          type(1byte->1char->int) groupId(1bytes->1char->1digit int {ie. 1,2,...,9}) nodeId(2bytes->2char->2digit int) /0
 *      Type 2 -- Data Packet:
 *          type(1byte->1char->int) groupId(1bytes->1char->1digit int {ie. 1,2,...,9}) nodeId(2bytes->2char->2digit int) data(123bytes) /0
 **/

class ChirpBluetoothPacket
{
    public:
        ChirpBluetoothPacket();
        ChirpBluetoothPacket(char[], size_t);
        int getPacketType();
        void setPacketType(int);
        bool isInitPacket();
        int getGroupId();
        void setGroupId(int);
        int getNodeId();
        void setNodeId(int);
        char* getData();
        void setData(char*);
        char* serialize();
    private:
        int packetType;
        int groupId;
        int nodeId;
        char data[MAX_BLUETOOTH_DATA_SIZE];
};
