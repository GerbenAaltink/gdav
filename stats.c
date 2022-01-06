#include "stats.h"
#include "humanize.h"
#include <stdio.h>
#include "functions.h"
#include "log.h"
#include "malloc.h"
#include "humanize.h"

extern Stats stats;
extern bool LOG_STATS;

const char* strstat(Stats st)
{
    static char str[1024];


    sprintf(str,
        "sent: %s\t"
        "recv: %s\t"
        "c: %ld\t"
        "tc: %ld",
        humanize_bytes(st.bytesSent), humanize_bytes(st.bytesReceived), st.connectionCount,
        st.connectionCountMax);
    return str;
}

char * stats_html(Stats st, char * document) {
    czero(document);
    csprintf(document, "<table>\n");
    csprintf(document, "<tr><th>%s</th><td>%ld</td></tr>\n", "Total accepted:", st.connectionCount);
    csprintf(document, "<tr><th>%s</th><td>%ld</td></tr>\n", "Max concurrency:", st.connectionCountMax);
    csprintf(document, "<tr><th>%s</th><td>%s</td></tr>\n", "Bytes sent:", humanize_bytes(st.bytesSent));
    csprintf(document, "<tr><th>%s</th><td>%s</td></tr>\n", "Bytes received:", humanize_bytes(st.bytesReceived));
    csprintf(document, "<tr><th>%s</th><td>%ld</td></tr>\n", "Requests started:", st.requestCount);
    csprintf(document, "<tr><th>%s</th><td>%ld</td></tr>\n", "Requests done:", st.requestDone);
    csprintf(document, "<tr><th>%s</th><td>%ld</td></tr>\n", "Requests error:", st.requestError);
    csprintf(document, "<tr><th>%s</th><td>%ld</td></tr>\n", "Requests chunks:", st.requestChunks);
    csprintf(document, "<tr><th>%s</th><td>%s</td></tr>\n", "Memory allocated", humanize_bytes(httpc_allocated));
    csprintf(document, "<tr><th>%s</th><td>%s</td></tr>\n", "Memory freed", humanize_bytes(httpc_freed));
    csprintf(document, "<tr><th>%s</th><td>%s</td></tr>\n", "Memory allocated peak", humanize_bytes(httpc_allocated_max));
    csprintf(document, "</table>\n");
    LogLine * line = log_tail(250);
    while(line) {
        csprintf(document, "%s<br />\n", strtrimr(line->line,'\n'));
        line = line->next;
    }
    return document;
}
