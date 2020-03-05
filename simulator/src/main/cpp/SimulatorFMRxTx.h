#include <jni.h>

#include "ChirpFMRxTx.h"

#define clazz "VirtualDeviceWrapper"

class SimulatorFMRxTx: public ChirpFMRxTx
{
    public:
        SimulatorFMRxTx();
        void init(JNIEnv* env, jobject obj);
        void send(int, char[], size_t);
        char* receive();
        int getToAddress(char[]);
    private:
        JNIEnv* env;
        jobject obj;
        char* getCharsFromJByteArray(jbyteArray);
};
