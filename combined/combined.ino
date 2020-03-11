
#include "NRF52RxTx.h"
#include "RFM69RxTx.h"

NRF52RxTx blue_io = NRF52RxTx();
RFM69RxTx radio_io = RFM69RxTx();

// Setup
void setup()
{
  radio_io.init();

  blue_io.init();
}

/**************************************************************************/
/*
    @brief  Poll for recieve from BLE or Radio. Forward response based on origin
*/
/**************************************************************************/
void loop()
{
  char packet[122] = {NULL};
  blue_io.receive(packet);
  if (packet[0])
  {
    Serial.println("Sending over radio");
    Serial.println(packet);
    bool received = false;
    while (!received) {
      radio_io.send(1, packet, sizeof(packet));
      char payload[122] = {NULL};
      radio_io.receive(payload);
      if (payload[0])
      {
        received = true;
        Serial.println("Sending to phone from radio");
        Serial.println(payload);
        blue_io.send(payload, sizeof(payload));
      }
    }
  }
}
