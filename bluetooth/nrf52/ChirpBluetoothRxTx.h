class ChirpBluetoothRxTx
{
    public:
        virtual void send(char[], size_t) = 0;
        virtual char* receive() = 0;
};
