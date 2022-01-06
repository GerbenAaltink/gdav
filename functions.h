#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

size_t readline(char * line, size_t length, FILE * fd);

char * czero(char * val);

char * strtrim(char * str, char chr);
char * strtriml(char * str, char chr);
char * strtrimr(char * str, char chr);

bool streq(char* string1, char* string2);

char * csprintf(char* target, const char* fmt, ...);
