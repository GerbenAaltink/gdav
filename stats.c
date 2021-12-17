#include "stats.h"
#include "humanize.h"
#include <stdio.h>

extern Stats stats;
extern bool LOG_STATS;

const char* strstat(Stats st)
{
    static char str[1024];

    char* human_bytes_sent = humanize_bytes(st.bytesSent);
    char* human_bytes_received = humanize_bytes(st.bytesReceived);

    sprintf(str,
        "sent: %s\t"
        "recv: %s\t"
        "c: %ld\t"
        "tc: %ld",
        human_bytes_sent, human_bytes_received, st.connectionCount,
        st.connectionCountMax);
    return str;

    free(human_bytes_sent);
    free(human_bytes_received);
}
