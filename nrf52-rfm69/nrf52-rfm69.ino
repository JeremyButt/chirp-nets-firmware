
#include "NRF52RxTx.h"
#include "RFM69RxTx.h"
#include "ChirpRouting.h"

NRF52RxTx bluetooth = NRF52RxTx();
RFM69RxTx radio = RFM69RxTx();
ChirpRouter router = ChirpRouter();

// Setup
void setup()
{
  radio.init();
  bluetooth.init();
	router.init(&radio);
}

/**************************************************************************/
/*
    @brief  Poll for recieve from BLE or Radio. Forward response based on origin
*/
/**************************************************************************/
void loop()
{
  char* bluetoothPacket;
  bluetooth.receive(bluetoothPacket);
	if(bluetoothPacket != nullptr)
	{
		router.send(bluetoothPacket, strlen(bluetoothPacket));
	}

	char* receivedData = router.receive();
	if(receivedData != nullptr)
	{
		bluetooth.send(receivedData, strlen(receivedData));
	}
  // char packet[122] = {NULL};
  // blue_io.receive(packet);
  // if (packet[0])
  // {
  //   Serial.println("Sending over radio");
  //   Serial.println(packet);
  //   radio_io.send(2, packet, sizeof(packet));
  // }

  // char payload[122] = {NULL};
  // radio_io.receive(payload);
  // if (payload[0])
  // {
  //   Serial.println("Sending to phone from radio");
  //   Serial.println(payload);
  //   blue_io.send(payload, sizeof(payload));
  // }
}
