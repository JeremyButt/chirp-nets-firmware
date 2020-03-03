#include<jni.h>
#include <iostream>

#include "SimulatorFMRxTx.h"

SimulatorFMRxTx::SimulatorFMRxTx()
{
}

void SimulatorFMRxTx::init(JNIEnv* env, jobject obj)
{
    this->env = env;
    this->obj = obj;
}

void SimulatorFMRxTx::send(int toAddress, char payload[], size_t len)
{
    jclass cls = this->env->FindClass(clazz);
    jmethodID m_id = this->env->GetMethodID(cls, "send", "(I[B)V");
    if (m_id != 0)
    {
        jbyteArray packet = this->env->NewByteArray(len);
        this->env->SetByteArrayRegion(packet, 0, len, reinterpret_cast<jbyte*>(payload));
        this->env->CallVoidMethod(this->obj, m_id, toAddress, packet);
    }
    else
    {
        std::cout << "ERROR: Function \"send\" not found!" << std::endl;
    }
}

char* SimulatorFMRxTx::receive()
{
    jclass cls = this->env->FindClass(clazz);
    jmethodID m_id = this->env->GetMethodID(cls, "receive", "()[B");
    if (m_id != 0)
    {
        jbyteArray packet = (jbyteArray)this->env->CallObjectMethod(this->obj, m_id);
        if(packet != 0)
        {
            return getCharsFromJByteArray(packet);
        }
        return nullptr;
    }
    else
    {
        std::cout << "ERROR: Function \"receive\" not found!" << std::endl;
    }
}

int SimulatorFMRxTx::getToAddress(char packet[])
{
    return (int)((int)packet[0]) - 48;
}

char* SimulatorFMRxTx::getCharsFromJByteArray(jbyteArray array)
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
