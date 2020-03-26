#include <string>
#include "VirtualDeviceWrapper.h"
#include "SimulatorFMRxTx.h"
#include "SimulatorBluetoothRxTx.h"
#include "ChirpRouting.h"
#include "utils.h"

/*HELPERS*/
void set_radio(JNIEnv *env, jobject obj, SimulatorFMRxTx* radio);
SimulatorFMRxTx* get_radio(JNIEnv *env, jobject obj);
void set_bluetooth(JNIEnv *env, jobject obj, SimulatorBluetoothRxTx* bluetooth);
SimulatorBluetoothRxTx* get_bluetooth(JNIEnv *env, jobject obj);
void set_router(JNIEnv *env, jobject obj, ChirpRouter* router);
ChirpRouter* get_router(JNIEnv *env, jobject obj);


JNIEXPORT void JNICALL Java_VirtualDeviceWrapper_init(JNIEnv *env, jobject obj)
{
	SimulatorFMRxTx* radio = new SimulatorFMRxTx();
	SimulatorBluetoothRxTx* bluetooth = new SimulatorBluetoothRxTx();
	ChirpRouter* router = new ChirpRouter();
	
	radio->init(env, obj);
	bluetooth->init(env, obj);
	router->init(radio);

	set_radio(env, obj, radio);
	set_bluetooth(env, obj, bluetooth);
	set_router(env, obj, router);
}

JNIEXPORT void JNICALL Java_VirtualDeviceWrapper_loop(JNIEnv *env, jobject obj)
{
	SimulatorFMRxTx* radio = get_radio(env, obj);
	SimulatorBluetoothRxTx* bluetooth = get_bluetooth(env, obj);
	ChirpRouter* router = get_router(env, obj);

	radio->init(env, obj);
	bluetooth->init(env, obj);
	router->init(radio);

	char* bluetoothPacket = bluetooth->receive();
	if(bluetoothPacket != nullptr)
	{
		router->send(bluetoothPacket, strlen(bluetoothPacket));
	}

	char* receivedData = router->receive();
	if(receivedData != nullptr)
	{
		bluetooth->send(receivedData, strlen(receivedData));
	}
}

/*HELPERS*/
//bluetooth
jfieldID get_bluetoothPtr_FieldId(JNIEnv * env, jobject obj)
{
    static jfieldID ptrFieldId = 0;

    if (!ptrFieldId)
    {
        jclass c = env->GetObjectClass(obj);
        ptrFieldId = env->GetFieldID(c, "bluetoothPtr", "J");
    }
    return ptrFieldId;
}

void set_bluetooth(JNIEnv *env, jobject obj, SimulatorBluetoothRxTx* bluetooth)
{
	env->SetLongField(obj, get_bluetoothPtr_FieldId(env, obj), (jlong) bluetooth);
}

SimulatorBluetoothRxTx* get_bluetooth(JNIEnv *env, jobject obj)
{
	return (SimulatorBluetoothRxTx*) env->GetLongField(obj, get_bluetoothPtr_FieldId(env, obj));
}

//radio
jfieldID get_radioPtr_FieldId(JNIEnv * env, jobject obj)
{
    static jfieldID ptrFieldId = 0;

    if (!ptrFieldId)
    {
        jclass c = env->GetObjectClass(obj);
        ptrFieldId = env->GetFieldID(c, "radioPtr", "J");
    }
    return ptrFieldId;
}

void set_radio(JNIEnv *env, jobject obj, SimulatorFMRxTx* radio)
{
	env->SetLongField(obj, get_radioPtr_FieldId(env, obj), (jlong) radio);
}

SimulatorFMRxTx* get_radio(JNIEnv *env, jobject obj)
{
	return (SimulatorFMRxTx*) env->GetLongField(obj, get_radioPtr_FieldId(env, obj));
}

//router
jfieldID get_routerPtr_FieldId(JNIEnv * env, jobject obj)
{
    static jfieldID ptrFieldId = 0;

    if (!ptrFieldId)
    {
        jclass c = env->GetObjectClass(obj);
        ptrFieldId = env->GetFieldID(c, "routerPtr", "J");
    }
    return ptrFieldId;
}

void set_router(JNIEnv *env, jobject obj, ChirpRouter* router)
{
	env->SetLongField(obj, get_routerPtr_FieldId(env, obj), (jlong) router);
}

ChirpRouter* get_router(JNIEnv *env, jobject obj)
{
	return (ChirpRouter*) env->GetLongField(obj, get_routerPtr_FieldId(env, obj));
}
