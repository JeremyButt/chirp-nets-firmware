class ChirpFMRxTx
{
    public:
        virtual void send(int, char[], size_t) = 0;
        virtual void receive(char[]) = 0;
        virtual int getToAddress(char[]) = 0;
};
