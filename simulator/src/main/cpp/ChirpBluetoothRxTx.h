
class ChirpBluetoothRxTx
{
    public:
        virtual void send(char[], size_t) = 0;
        virtual void receive(char[]) = 0;
};
