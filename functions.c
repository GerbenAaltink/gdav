#include "functions.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

char * strtrim(char * str, char chr){
    return strtriml(strtrimr(str, chr),chr);
}

char * strtriml(char * str, char chr){ 
    while(str && strlen(str)){
        if(str[0] == chr)
            strcpy(str, str+1);
        else
            break;
    }
    return str;
}

char * strtrimr(char * str, char chr){ 
    while(str && strlen(str)){
        if(str[strlen(str) - 1] == chr)
            str[strlen(str) - 1] = 0;
        else
            break;
    }
    return str;
}

bool streq(char* string1, char* string2)
{
    return strcmp(string1, string2) == 0;
}

void csprintf(char* target, const char* fmt, ...)
{
    char buffer[4096];
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    strcat(target, buffer);
}
