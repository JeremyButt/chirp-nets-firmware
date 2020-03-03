#include <jni.h>

#include "ChirpRxTx.h"

#define clazz "VirtualDeviceWrapper"

class SimulatorRxTx: public ChirpRxTx
{
    public:
        SimulatorRxTx();
        void init(JNIEnv* env, jobject obj);
        void send(int, char[], size_t);
        char* receive();
        void sendBluetooth(char[], size_t);
        char* receiveBluetooth();
        int getToAddress(char[]);
    private:
        JNIEnv* env;
        jobject obj;
        char* getCharsFromJByteArray(jbyteArray);
};