#include "ChirpBluetoothRxTx.h"
#include <bluefruit.h>

// Function prototypes for packetparser.cpp
uint8_t readPacket (BLEUart *ble_uart, uint16_t timeout);
float   parsefloat (uint8_t *buffer);
void    printHex   (const uint8_t * data, const uint32_t numBytes);

// Packet buffer
extern uint8_t packetbuffer[];

class NRF52RxTx: public ChirpBluetoothRxTx
{
    public:
        NRF52RxTx();
        void init();
        void send(char[], int);
        char* receive();
};
