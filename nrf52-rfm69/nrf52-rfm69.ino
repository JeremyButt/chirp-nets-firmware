
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
	char bluetoothPacket[128] = {NULL};
	bluetooth.receive(bluetoothPacket);
	if(bluetoothPacket[0] != NULL)
	{
		router.send(bluetoothPacket, strlen(bluetoothPacket));
	}
	char receivedData[128] = {NULL};
	router.receive(receivedData);
	if(receivedData[0] != NULL)
	{
		bluetooth.send(receivedData, strlen(receivedData));
	}
}
