
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
/*!
    @brief  Constantly poll for new command or response data
*/
/**************************************************************************/
void loop()
{
  char *packet = blue_io.receive();
  
  if (packet)
  {
    Serial.println("Sending over radio");
    radio_io.send(1, packet, sizeof(packet));
  }

  char *payload = radio_io.receive();
  if (payload) {
    Serial.println("Sending to phone from radio");
    blue_io.send(payload, sizeof(payload));
  }
}
