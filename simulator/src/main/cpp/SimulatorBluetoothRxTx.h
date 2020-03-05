#include <jni.h>

#include "ChirpBluetoothRxTx.h"

#define clazz "VirtualDeviceWrapper"

class SimulatorBluetoothRxTx: public ChirpBluetoothRxTx
{
    public:
        SimulatorBluetoothRxTx();
        void init(JNIEnv* env, jobject obj);
        void send(char[], size_t);
        char* receive();
    private:
        JNIEnv* env;
        jobject obj;
        char* getCharsFromJByteArray(jbyteArray);
};
