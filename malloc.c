#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "malloc.h"
#include "utlist.h"
#include "config.h"

extern size_t httpc_allocated;
extern size_t httpc_freed;
extern size_t httpc_allocated_max;

int ptrcmp(HTTPC_Malloc* a, HTTPC_Malloc* b)
{
     return !(a->ptr == b->ptr);
}


HTTPC_Malloc * httpc_malloc_append() {
    HTTPC_Malloc* m = malloc(sizeof(HTTPC_Malloc));
    DL_APPEND(httpc_malloced, m);
    return m;
}

#if HTTPC_MALLOC_ENABLED
void* httpc_malloc(size_t size)
{
    httpc_allocated += size;
    HTTPC_Malloc* m = httpc_malloc_append();
    void* result = malloc(size);
    m->ptr = result;
    m->size = size;
    LOG_DEBUG("Malloc: %p allocated %zu bytes\n", result, m->size);
    if (httpc_allocated > httpc_allocated_max)
        httpc_allocated_max = httpc_allocated;
    return result;
}
void httpc_free(void* ptr)
{
    HTTPC_Malloc* result;
    HTTPC_Malloc* temp = malloc(sizeof(HTTPC_Malloc));
    temp->ptr = ptr;
    DL_SEARCH(httpc_malloced, result, temp, ptrcmp);
    if (result) {
        httpc_freed += result->size;
        size_t size = result->size;
        free(result->ptr);
        DL_DELETE(httpc_malloced, result);
        httpc_allocated -= size;
        LOG_DEBUG("Malloc: %p freed %zu bytes\n", ptr, size);
    } else {
        LOG_ERROR("Malloc: failed free for pointer. Double free?\n");
    }
    free(temp);
}
#else
void * httpc_malloc(size_t size){
    return malloc(size);
}
void httpc_free(void * ptr){
    free(ptr);
}
#endif

