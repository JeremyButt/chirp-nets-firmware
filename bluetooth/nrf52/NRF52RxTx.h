#include <bluefruit.h>
#include <SPI.h>                // Included with Arduino IDE, should also add https://github.com/LowPowerLab/SPIFlash
#include "ChirpBluetoothRxTx.h"

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
        void send(char[], size_t);
        char* receive();
};
