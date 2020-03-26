#include <jni.h>

#include "ChirpFMRxTx.h"

#define clazz "VirtualDeviceWrapper"

class SimulatorFMRxTx: public ChirpFMRxTx
{
    public:
        SimulatorFMRxTx();
        void init(JNIEnv*, jobject);
        void send(int, char[], size_t);
        char* receive();
    private:
        JNIEnv* env;
        jobject obj;
        char* getCharsFromJByteArray(jbyteArray);
};
