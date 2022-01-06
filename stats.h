#pragma once

#include <stdbool.h>

typedef struct Stats {
    unsigned long bytesSent;
    unsigned long bytesReceived;
    unsigned long connectionCount;
    unsigned long connectionCountMax;
    unsigned long requestCount;
    unsigned long requestDone;
    unsigned long requestError;
    unsigned long requestChunks;
    unsigned long requestExecuting;
    
} Stats;

Stats stats;
bool LOG_STATS;

const char* strstat(Stats st);