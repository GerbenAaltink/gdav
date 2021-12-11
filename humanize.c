#include <string.h>

#include <stdio.h>
#include "humanize.h"

char* humanize_bytes(size_t bytes)
{
    char suffix[2];
    double value;

    double gb = 1024 * 1024 * 1024;
    double mb = 1024 * 1024;
    double kb = 1024;

    if (bytes > gb) {
        strcpy(suffix, "GB");
        value = bytes / gb;
    } else if (bytes > 1024 * 1024) {
        strcpy(suffix, "MB");
        value = bytes / mb;
    } else if (bytes > 1024) {
        strcpy(suffix, "KB");
        value = bytes / kb;
    } else {
        strcpy(suffix, "b");
        value = bytes;
    }
    char* result = (char*)malloc(100);
    sprintf(result, "%2.f %s", value, suffix);
    return result;
}