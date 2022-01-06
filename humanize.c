#include <string.h>

#include "humanize.h"
#include <stdio.h>

char* humanize_bytes(size_t bbytes)
{
    char suffix[3];
    double value;

    float bytes = bbytes;

    double gb = 1024.0 * 1024.0 * 1024.0;
    double mb = 1024.0 * 1024.0;
    double kb = 1024.0;

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
    static char result[100];
    sprintf(result, "%10.2f %s", value, suffix);
    return result;
}