#include "RFM69RxTx.h"

RFM69RxTx radio = RFM69RxTx();

// Setup
void setup() {
  radio.init();
}

void loop() {

    char[] packet = radio.receive();

    char[] payload = "Hello World!";
    radio.send(1, payload, sizeof(payload);
}