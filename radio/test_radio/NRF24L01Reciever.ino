#include "NRF24L01Reciever.h"

void NRRF24L01Reciver::setup() {
      Serial.begin(9600);
      radio.begin();
      radio.openReadingPipe(0, address);
      radio.setPALevel(RF24_PA_MIN);
      radio.startListening();
    }
void NRRF24L01Reciver::listen() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
    }
  }
}