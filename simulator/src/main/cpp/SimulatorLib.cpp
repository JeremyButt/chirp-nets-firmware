#include "SimulatorLib.h"

#include <iostream>

void send(JNIEnv *env, jobject obj, int toAddress, char payload[], size_t len)
{
    jclass cls = env->FindClass(clazz);
    jmethodID m_id = env->GetMethodID(cls, "send", "(I[B)V");
    if (m_id != 0)
    {
        jbyteArray packet = env->NewByteArray(len);
        env->SetByteArrayRegion(packet, 0, len, reinterpret_cast<jbyte*>(payload));
        env->CallVoidMethod(obj, m_id, toAddress, packet);
    }
    else
    {
        std::cout << "ERROR: Function \"send\" not found!" << std::endl;
    }
}

char* receive(JNIEnv *env, jobject obj)
{
    jclass cls = env->FindClass(clazz);
    jmethodID m_id = env->GetMethodID(cls, "receive", "()[B");
    if (m_id != 0)
    {
        jbyteArray packet = (jbyteArray)env->CallObjectMethod(obj, m_id);
        if(packet != 0)
        {
            return getCharsFromJByteArray(env, packet);
        }
        return nullptr;
    }
    else
    {
        std::cout << "ERROR: Function \"receive\" not found!" << std::endl;
    }
}

char* receiveBluetooth(JNIEnv *env, jobject obj)
{
    jclass cls = env->FindClass(clazz);
    jmethodID m_id = env->GetMethodID(cls, "recieveBluetoothPacket", "()[B");
    if (m_id != 0)
    {
        jbyteArray packet = (jbyteArray)env->CallObjectMethod(obj, m_id);
        if(packet != 0)
        {
            return getCharsFromJByteArray(env, packet);
        }
        return nullptr;
    }
    else
    {
        std::cout << "ERROR: Function \"recieveBluetoothPacket\" not found!" << std::endl;
    }
}

void sendBluetooth(JNIEnv *env, jobject obj, char payload[], size_t len)
{
    jclass cls = env->FindClass(clazz);
    jmethodID m_id = env->GetMethodID(cls, "sendBluetoothPacket", "([B)V");
    if (m_id != 0)
    {
        jbyteArray packet = env->NewByteArray(len);
        env->SetByteArrayRegion(packet, 0, len, reinterpret_cast<jbyte*>(payload));
        env->CallVoidMethod(obj, m_id, packet);
    }
    else
    {
        std::cout << "ERROR: Function \"sendBluetoothPacket\" not found!" << std::endl;
    }
}

int getToAddress(char packet[])
{
    return (int)((int)packet[0]) - 48;
}

char* getCharsFromJByteArray(JNIEnv *env, jbyteArray array)
{
    char *chars = NULL;
    jbyte *bytes;
    bytes = env->GetByteArrayElements(array, 0);
    int chars_len = env->GetArrayLength(array);
    chars = new char[chars_len + 1];
    memset(chars,0,chars_len + 1);
    memcpy(chars, bytes, chars_len);
    chars[chars_len] = 0;
    env->ReleaseByteArrayElements(array, bytes, 0);
    return chars;
}
