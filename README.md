# Chirp Nets Firmware
Firmware for Chirp Nets Mesh Network Device


# Running on Device
Currently the Chirp Nets Firmware supports a single hardware configuration, using a nRF52 microcontroller with built in bluetooth transciever and a RFM69 915Mhz radio transciever

## 1. Setup Your nRF52 Board
This can be completed by following the instructions layed out by Adafruit on the [nRF52 featherwing learning page](https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/arduino-bsp-setup)

## 2. Download the LowPowerLibs RFM69 Library into your Ardiuno Folder

The library for the RFM69 radio board can be found on [our fork](https://github.com/chirpnets/RFM69)
Download the library and unzip it into the /Ardiuno/Libraries directory

## 3. Compile Firmware
The code for this configuration is contained within the nrf52-rfm69 folder.

To run this code on a device, open the combined.ino file in the Ardiuno IDE and add the .h and .cpp files in the directory to the sketch. 
You can now upload to the device and connect the Chirp Nets mobile application

If you have any issues or question feel free to open a github issue and we should respond promptly
