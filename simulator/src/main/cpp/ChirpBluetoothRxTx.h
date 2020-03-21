
class ChirpBluetoothRxTx
{
    public:
        virtual void send(char[], size_t);
        virtual char* receive();
};
