
#include "NRF52RxTx.h"

NRF52RxTx blue_io = NRF52RxTx();

// Setup
void setup() {
  blue_io.init();
}


/**************************************************************************/
/*!
    @brief  Constantly poll for new command or response data
*/
/**************************************************************************/
void loop() {

    char* packet = blue_io.receive();

    char* payload = "Hello World!";
    blue_io.send(payload, sizeof(payload));
}
