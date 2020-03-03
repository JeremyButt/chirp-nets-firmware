#include "VirtualDeviceWrapper.h"
#include "SimulatorLib.h"
#include <iostream>



JNIEXPORT void JNICALL Java_VirtualDeviceWrapper_main(JNIEnv *env, jobject obj)
{
	SimulatorRxTx rxtx = SimulatorRxTx();
	rxtx.init(env, obj);

	char* bluetoothPacket = rxtx.receiveBluetooth();
	if(bluetoothPacket != nullptr)
	{
		int toAddress = rxtx.getToAddress(bluetoothPacket);
		char* payload = bluetoothPacket;
		rxtx.send(toAddress, payload, strlen(payload));
	}

	
	char* receivedData = rxtx.receive();
	if(receivedData != nullptr)
	{
		rxtx.sendBluetooth(receivedData, strlen(receivedData));
	}
}
