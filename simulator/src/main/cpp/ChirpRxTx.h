
class ChirpRxTx
{
    public:
        virtual void send(int, char[], size_t) = 0;
        virtual char* receive() = 0;
        virtual void sendBluetooth(char[], size_t) = 0;
        virtual char* receiveBluetooth() = 0;
        virtual int getToAddress(char[]) = 0;
};