#include <bluefruit.h>
#include <SPI.h>                // Included with Arduino IDE, should also add https://github.com/LowPowerLab/SPIFlash
#include "ChirpBluetoothRxTx.h"

class NRF52RxTx: public ChirpBluetoothRxTx
{
    public:
        NRF52RxTx();
        void init();
        void send(char[], size_t);
        char* receive();
    private:
        void startAdv(void);
        BLEDfu bledfu;
        BLEUart bleuart;
};
