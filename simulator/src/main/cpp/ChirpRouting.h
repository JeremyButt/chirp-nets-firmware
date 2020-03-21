#include <ctime>
#include "ChirpRadioPacket.h"
#include "ChirpBluetoothPacket.h"

#define MAX_PAYLOAD_SIZE 20 // bytes

#define MAX_MESSAGE_SEGMENTS_CACHE_SIZE 128 // entries
#define MAX_MESSAGE_SEGMENTS_CACHE_TIMEOUT 120 // seconds in epoch

#define MAX_HISTORY_CACHE_SIZE 128
#define MAX_HISTORY_CACHE_TIMEOUT 120 // seconds in epoch

#define BROADCAST_ADDR 0
#define IS_SIMULATOR true

struct MessageSegmentCacheEntry
{
    time_t time_stamp;
    ChirpRadioPacket message_segment;
};

struct HistoryEntry
{
    time_t time_stamp;
    int source_id;
    int group_id;
    int packet_id;
    int sequence_number;
};

class ChirpRouter
{
    public:
        ChirpRouter();
        void init(ChirpFMRxTx*);
        void send(char[], size_t);
        char* receive();
        
    private:
        ChirpFMRxTx* radio;
        int messageId;
        int groupId;
        int nodeId;
        int messageSegmentCacheSize;
        struct MessageSegmentCacheEntry messageSegmentsCache[MAX_MESSAGE_SEGMENTS_CACHE_SIZE];
        int historyCacheSize;
        struct HistoryEntry history[MAX_HISTORY_CACHE_SIZE];
        bool checkRouteCache(int);
        void neighborNodeDiscovery();
        void cacheMaintenance();
        void messageSegmentCacheMaintenance();
        void historyCacheMaintenance();
        void addToMessageSegmentCache(ChirpRadioPacket);
        void addToHistoryCache(ChirpRadioPacket);
        bool aleadyReceived(ChirpRadioPacket);
        ChirpBluetoothPacket* getMessageFromCache(ChirpRadioPacket);
};