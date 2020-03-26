
class ChirpFMRxTx
{
    public:
        virtual void send(int, char[], size_t) = 0;
        virtual char* receive() = 0;
        int getNodeId();
        int getGroupId();
        void setNodeId(int);
        void setGroupId(int);
    private:
        int deviceId;
        int groupId;
        int nodeId;
};
