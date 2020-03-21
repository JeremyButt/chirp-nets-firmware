
class ChirpFMRxTx
{
    public:
        virtual void send(int, char[], size_t);
        virtual char* receive();
        int getNodeId();
        int getGroupId();
        void setNodeId(int);
        void setGroupId(int);
    private:
        int deviceId;
        int groupId;
        int nodeId;
};
