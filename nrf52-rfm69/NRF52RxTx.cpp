#include "NRF52RxTx.h"

NRF52RxTx::NRF52RxTx()
{
    this->bledfu = BLEDfu();
    this->bleuart = BLEUart();
}

void NRF52RxTx::startAdv(void)
{
    // Advertising packet
    Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
    Bluefruit.Advertising.addTxPower();

    // Include the BLE UART (AKA 'NUS') 128-bit UUID
    Bluefruit.Advertising.addService(bleuart);

    // Secondary Scan Response packet (optional)
    // Since there is no room for 'Name' in Advertising packet
    Bluefruit.ScanResponse.addName();

    /* Start Advertising
     - Enable auto advertising if disconnected
     - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
     - Timeout for fast mode is 30 seconds
     - Start(timeout) with timeout = 0 will advertise forever (until connected)

     For recommended advertising interval
     https://developer.apple.com/library/content/qa/qa1931/_index.html
  */
    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(32, 244); // in unit of 0.625 ms
    Bluefruit.Advertising.setFastTimeout(30);   // number of seconds in fast mode
    Bluefruit.Advertising.start(0);             // 0 = Don't stop advertising after n seconds
}

void NRF52RxTx::init()
{
    Serial.begin(115200);
    while (!Serial)
        delay(10); // for nrf52840 with native usb

    Serial.println(F("Adafruit Bluefruit52 Controller App Example"));
    Serial.println(F("-------------------------------------------"));

    Bluefruit.begin();
    Bluefruit.setTxPower(4); // Check bluefruit.h for supported values
    Bluefruit.setName("Bluefruit52");

    // To be consistent OTA DFU should be added first if it exists
    this->bledfu.begin();

    // Configure and start the BLE Uart service
    this->bleuart.begin();

    // Set up and start advertising
    startAdv();
    Serial.println(F("Please use Adafruit Bluefruit LE app to connect in Controller mode"));
    Serial.println(F("Then activate/use the sensors, color picker, game controller, etc!"));
    Serial.println();
}

void NRF52RxTx::send(char payload[], size_t len)
{
    // Forward data from HW Serial to BLEUART
    bleuart.write(payload, len);
    Serial.println("Written");
}

void NRF52RxTx::receive(char ch[])
{
    // Forward from BLEUART to HW Serial
    int i = 0;
    while (bleuart.available())
    {
        ch[i++] = (char)bleuart.read();
        Serial.println(ch[i]);
    }
}

bool NRF52RxTx::checkChecksum(char packet[], size_t len)
{
    uint8_t xsum = 0;
    uint8_t checksum = packet[len - 1];
    for (uint8_t i = 0; i < len - 1; i++)
    {
        xsum += packet[i];
    }
    xsum = ~xsum;
    if (xsum != checksum)
    {
        return false;
    }
    return true;
}

uint8_t NRF52RxTx::getChecksum(char packet[], size_t len)
{
    uint8_t xsum = 0;
    for (uint8_t i = 0; i < len - 1; i++)
    {
        xsum += packet[i];
    }
    xsum = ~xsum;
    return xsum;
}
