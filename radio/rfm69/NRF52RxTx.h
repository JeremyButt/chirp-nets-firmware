#include "ChirpBluetoothRxTx.h"

class NRF52RxTx: public ChirpBluetoothRxTx
{
    public:
        void send(char[], size_t);
        char* receive();
};
