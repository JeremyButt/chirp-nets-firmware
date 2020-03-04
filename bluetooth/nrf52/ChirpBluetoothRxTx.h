
class ChirpBluetoothRxTx
{
    public:
        virtual void send(char[], int) = 0;
        virtual char* receive() = 0;
};
