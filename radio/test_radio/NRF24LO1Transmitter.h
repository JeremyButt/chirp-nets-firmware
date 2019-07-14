    /*
    * Arduino Wireless Communication Tutorial
    *     Example 1 - Transmitter Code
    *                
    * by Dejan Nedelkovski, www.HowToMechatronics.com
    * 
    * Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
    */
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "transmitter.h"

class NRRF24L01Transmitter extends Transmitter{
    public:
        NRRF24L01Transmitter();
        void setup();
        void send();
    private:
        RF24 radio(7, 8); // CE, CSN
        const byte address[6] = "00001";
}