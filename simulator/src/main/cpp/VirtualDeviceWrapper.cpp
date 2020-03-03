#include "VirtualDeviceWrapper.h"
#include "SimulatorFMRxTx.h"
#include "SimulatorBluetoothRxTx.h"
#include <iostream>



JNIEXPORT void JNICALL Java_VirtualDeviceWrapper_main(JNIEnv *env, jobject obj)
{
	SimulatorFMRxTx radio = SimulatorFMRxTx();
	SimulatorBluetoothRxTx bluetooth = SimulatorBluetoothRxTx();
	radio.init(env, obj);
	bluetooth.init(env, obj);

	char* bluetoothPacket = bluetooth.receive();
	if(bluetoothPacket != nullptr)
	{
		int toAddress = radio.getToAddress(bluetoothPacket);
		char* payload = bluetoothPacket;
		radio.send(toAddress, payload, strlen(payload));
	}

	
	char* receivedData = radio.receive();
	if(receivedData != nullptr)
	{
		bluetooth.send(receivedData, strlen(receivedData));
	}
}
