#include "ChirpBluetoothRxTx.h"

class NRF52RxTx: public ChirpBluetoothRxTx
{
    public:
        void send(char[], int);
        char* receive();
};
