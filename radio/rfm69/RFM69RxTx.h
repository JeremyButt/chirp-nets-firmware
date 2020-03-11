#include <RFM69.h>              // https://www.github.com/lowpowerlab/rfm69
#include <RFM69_ATC.h>          // https://www.github.com/lowpowerlab/rfm69
#include <SPI.h>                // Included with Arduino IDE, should also add https://github.com/LowPowerLab/SPIFlash
#include <ArduinoJson.h>        // https://arduinojson.org/

#include "ChirpFMRxTx.h"

// Node and network config
#define NODEID        2    // The ID of this node (must be different for every node on network)
#define NETWORKID     100  // The network ID

// Are you using the RFM69 Wing? Uncomment if you are.
#define USING_RFM69_WING 

// The transmision frequency of the baord. Change as needed.
#define FREQUENCY      RF69_915MHZ

// Uncomment if this board is the RFM69HW/HCW not the RFM69W/CW
#define IS_RFM69HW_HCW

// Serial board rate - just used to print debug messages
#define SERIAL_BAUD   115200

#define RF69_RESET      7   // "A"
#define RF69_SPI_CS      11   // "B"
#define RF69_INQ_PIN     30   // "D"
#define RF69_IRQ_NUM  digitalPinToInterrupt(RF69_IRQ_PIN)
#define LED           17

class RFM69RxTx: public ChirpFMRxTx
{
    public:
        RFM69RxTx();
        void init();
        void resetRadio();
        void send(int, char[], size_t);
        char* receive();
        int getToAddress(char[]);
    private:
        RFM69 radio;
};
