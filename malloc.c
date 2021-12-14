#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "malloc.h"
#include "utlist.h"

extern size_t httpc_allocated;
extern size_t httpc_freed;
extern size_t httpc_allocated_max;

int ptrcmp(HTTPC_Malloc* a, HTTPC_Malloc* b)
{
    return (a->ptr == b->ptr);
}

void* httpc_malloc(int size)
{
    httpc_allocated += size;
    HTTPC_Malloc* m = malloc(sizeof(HTTPC_Malloc));
    void* result = malloc(size);
    m->ptr = result;
    m->size = size;
    DL_APPEND(httpc_malloced, m);
    LOG_DEBUG("Malloc: allocated %zu\n", m->size);
    if (httpc_allocated > httpc_allocated_max)
        httpc_allocated_max = httpc_allocated;
    return malloc(size);
}

void httpc_free(void* ptr)
{
    HTTPC_Malloc* result;
    HTTPC_Malloc* temp;
    ///temp->ptr = ptr;
    free(ptr);
    return;

    DL_SEARCH(httpc_malloced, result, &temp, ptrcmp);
    if (result) {
        httpc_freed += result->size; ////result->size;
        size_t size = result->size;
        DL_DELETE(httpc_malloced, result);

        httpc_allocated -= size;
        LOG_DEBUG("Malloc: freed %zu\n", size);
    } else {
        LOG_ERROR("Malloc: failed free for pointer. Double free?\n");
    }
}
