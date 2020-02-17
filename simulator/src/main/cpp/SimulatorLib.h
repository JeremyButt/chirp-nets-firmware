#include <jni.h>

#define clazz "VirtualDeviceWrapper"

void send(JNIEnv*, jobject, int, char[], size_t);
char* receive(JNIEnv*, jobject);
char* receiveBluetooth(JNIEnv*, jobject);
void sendBluetooth(JNIEnv*, jobject, char[], size_t);
int getToAddress(char[]);
char* getCharsFromJByteArray(JNIEnv*, jbyteArray);
