#pragma once

#include <stdbool.h>

typedef struct Stats {
    long bytesSent;
    long bytesReceived;
    long connectionCount;
    long connectionCountMax;
} Stats;

Stats stats;
bool LOG_STATS;

const char* strstat(Stats st);