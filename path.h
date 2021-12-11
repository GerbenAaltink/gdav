#pragma once
#include <stdbool.h>

typedef struct Path {
    char* path;
    char* name;
    char* relativePath;
    char* extension;
    bool exists;
    bool is_dir;
    size_t size;
    char* mime_type;
    void* head;
    void* next;
} Path;

Path* path_info(char* path);

void free_path(Path * path);
