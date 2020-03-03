#include <RFM69.h>              // https://www.github.com/lowpowerlab/rfm69
#include <RFM69_ATC.h>          // https://www.github.com/lowpowerlab/rfm69
#include <SPI.h>                // Included with Arduino IDE
#include <ArduinoJson.h>        // https://arduinojson.org/d
#include "RFM69RxTx.h"

RFM69RxTx::RFM69RxTx()
{
}

RFM69RxTx::init()
{
    Serial.begin(115200);
    // Reset the radio
    resetRadio();
    // Initialize the radio
    radio.initialize(FREQUENCY, NODEID, NETWORKID);
    radio.promiscuous(true);
    #ifdef IS_RFM69HW_HCW
        radio.setHighPower(); //must include this only for RFM69HW/HCW!
    #endif
}

RFM69RxTx::resetRadio()
{
    if (Serial) Serial.print("Resetting radio...");
    pinMode(RF69_RESET, OUTPUT);
    digitalWrite(RF69_RESET, HIGH);
    delay(20);
    digitalWrite(RF69_RESET, LOW);
    delay(500);
}

void RFM69RxTx::send(int toAddress, char payload[], size_t len)
{
    unsigned long previousMillis = 0;
    const long sendInterval = 3000;
    // Send     
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= sendInterval) {
    previousMillis = currentMillis;

    if (Serial) Serial.println("Sending");
    if (radio.sendWithRetry(1, payload, len, 3, 200)) {
        if (Serial) Serial.println("ACK received");
    } else {
        if (Serial) Serial.println("No ACK");
    }
    }
}

char* RFM69RxTx::receive()
{
    // Receive
    if (radio.receiveDone()) 
    {
        if (Serial) Serial.println("Message received");
        if (radio.ACKRequested()) 
        { 
            radio.sendACK(); 
        }
        delay(100);
    }
}

void RFM69RxTx::sendBluetooth(char payload[], size_t len)
{
    //Tim's garb daddy code
}
    
char* RFM69RxTx::receiveBluetooth()
{
    //Tim's garb daddy code
}

int RFM69RxTx::getToAddress(char[] payload)
{
    return (int)((int)packet[0]) - 48;
}