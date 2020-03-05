#include "RFM69RxTx.h"

RFM69RxTx radio_io = RFM69RxTx();

// Setup
void setup() {
  radio_io.init();
}

void loop() {

    char* packet = radio_io.receive();

    char* payload = "Hello World!";
    radio_io.send(1, payload, sizeof(payload));
}
