#pragma once

typedef struct HTTPC_Malloc {
    void* ptr;
    int size;
    struct HTTPC_Malloc* next;
    struct HTTPC_Malloc* prev;
} HTTPC_Malloc;

size_t httpc_allocated;
size_t httpc_freed;
size_t httpc_allocated_max;

HTTPC_Malloc* httpc_malloced;

void* httpc_malloc(int size);

void httpc_free(void* ptr);
