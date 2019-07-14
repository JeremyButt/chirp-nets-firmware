#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "reciever.h"

class NRRF24L01Reciver extends Reciever{
    public:
        NRRF24L01Reciver();
        void setup();
        void listen();
    private:
        RF24 radio(7, 8); // CE, CSN
        const byte address[6] = "00001";
}