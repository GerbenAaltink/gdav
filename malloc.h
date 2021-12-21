#pragma once
#include <stddef.h>

typedef struct HTTPC_Malloc {
    void* ptr;
    size_t size;
    struct HTTPC_Malloc* next;
    struct HTTPC_Malloc* prev;
} HTTPC_Malloc;

size_t httpc_allocated;
size_t httpc_freed;
size_t httpc_allocated_max;

HTTPC_Malloc* httpc_malloced;

void* httpc_malloc(size_t size);

void httpc_free(void* ptr);
