#include <string.h>
#include <stdarg.h>
#include "functions.h"
#include <stdio.h>

bool streq(char* string1, char* string2)
{
    return strcmp(string1, string2) == 0;
}


void csprintf(char * target, const char* fmt, ...)
{
    char buffer[4096];
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    strcat(target, buffer);
}