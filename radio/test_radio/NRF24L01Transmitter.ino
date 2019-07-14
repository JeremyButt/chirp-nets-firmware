#include "NRF24L01Transmitter.h"

    void NRF24L01Transmitter::setup() {
      radio.begin();
      radio.openWritingPipe(address);
      radio.setPALevel(RF24_PA_MIN);
      radio.stopListening();
    }
    void NRF24L01Transmitter::send() {
      const char text[] = "Hello World";
      radio.write(&text, sizeof(text));
      delay(1000);
    }