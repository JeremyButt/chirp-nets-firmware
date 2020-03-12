#include <bluefruit.h>
#include <SPI.h>                // Included with Arduino IDE, should also add https://github.com/LowPowerLab/SPIFlash
#include "ChirpBluetoothRxTx.h"

class NRF52RxTx: public ChirpBluetoothRxTx
{
    public:
        NRF52RxTx();
        void init();
        void send(char[], size_t);
        void receive(char[]);
        bool checkChecksum(char[], size_t);
        uint8_t getChecksum(char[], size_t);
    private:
        void startAdv(void);
        BLEDfu bledfu;
        BLEUart bleuart;
};
