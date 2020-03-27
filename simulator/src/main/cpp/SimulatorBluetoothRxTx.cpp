#include <jni.h>
#include <iostream>

#include "SimulatorBluetoothRxTx.h"

SimulatorBluetoothRxTx::SimulatorBluetoothRxTx()
{
}

void SimulatorBluetoothRxTx::init(JNIEnv* env, jobject obj)
{
    this->env = env;
    this->obj = obj;
}

void SimulatorBluetoothRxTx::receive(char ch[])
{
    jclass cls = this->env->FindClass(clazz);
    jmethodID m_id = this->env->GetMethodID(cls, "receiveBluetoothPacket", "()[B");
    if (m_id != 0)
    {
        jbyteArray packet = (jbyteArray)this->env->CallObjectMethod(this->obj, m_id);
        if(packet != 0)
        {
            strcpy(ch, getCharsFromJByteArray(packet));
        }
    }
    else
    {
        std::cout << "ERROR: Function \"receiveBluetoothPacket\" not found!" << std::endl;
    }
}

void SimulatorBluetoothRxTx::send(char payload[], size_t len)
{
    jclass cls = this->env->FindClass(clazz);
    jmethodID m_id = this->env->GetMethodID(cls, "sendBluetoothPacket", "([B)V");
    if (m_id != 0)
    {
        jbyteArray packet = this->env->NewByteArray(len);
        this->env->SetByteArrayRegion(packet, 0, len, reinterpret_cast<jbyte*>(payload));
        this->env->CallVoidMethod(this->obj, m_id, packet);
    }
    else
    {
        std::cout << "ERROR: Function \"sendBluetoothPacket\" not found!" << std::endl;
    }
}

char* SimulatorBluetoothRxTx::getCharsFromJByteArray(jbyteArray array)
{
    char *chars = NULL;
    jbyte *bytes;
    bytes = this->env->GetByteArrayElements(array, 0);
    int chars_len = this->env->GetArrayLength(array);
    chars = new char[chars_len + 1];
    memset(chars,0,chars_len + 1);
    memcpy(chars, bytes, chars_len);
    chars[chars_len] = 0;
    this->env->ReleaseByteArrayElements(array, bytes, 0);
    return chars;
}
