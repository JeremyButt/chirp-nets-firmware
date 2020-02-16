#include "VirtualDeviceWrapper.h"
#include "SimulatorLib.h"
#include <iostream>



JNIEXPORT void JNICALL Java_VirtualDeviceWrapper_main(JNIEnv *env, jobject obj)
{
	char* bluetoothPacket = receiveBluetooth(env, obj);
	if(bluetoothPacket != nullptr)
	{
		int toAddress = getToAddress(bluetoothPacket);
		char* payload = bluetoothPacket;
		send(env, obj, toAddress, payload, strlen(payload));
	}

	
	char* receivedData = receive(env, obj);
	if(receivedData != nullptr)
	{
		sendBluetooth(env, obj, receivedData, strlen(receivedData));
	}
}