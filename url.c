#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
const char *URL_SPECIAL_CHARACTERS = "$%[]\\+=<>\"'~() ";

bool is_special_url_char(char chr)
{
    for (int i = 0; i < strlen(URL_SPECIAL_CHARACTERS); i++)
        if (chr == URL_SPECIAL_CHARACTERS[i])
            return true;
    return false;
}

int hex2int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}
char hex2intstr(char *str)
{
    return hex2int(str[0]) * 16 + hex2int(str[1]);
}

const char *url_decode(char *url)
{
    static char result[4096];
    result[0] = 0;
    for (int i = 0; i < strlen(url); i++)
    {
        char append[10];
        if (url[i] == '%')
        {
            char buff[2];
            buff[0] = url[i + 1];
            buff[1] = url[i + 2];
            sprintf(append, "%c", hex2intstr(buff));
            i += 2;
        }
        else
        {
            sprintf(append, "%c", url[i]);
        }
        strcat(result, append);
    }
    return result;
}

const char *url_encode(char *url)
{
    static char result[4096];
    result[0] = 0;
    for (int i = 0; i < strlen(url); i++)
    {
        char chr = url[i];
        char append[10];
        if (is_special_url_char(chr))
        {
            sprintf(append, "%%%x", chr);
            append[2] = toupper(append[2]);
        }
        else
        {
            sprintf(append, "%c", chr);
        }
        strcat(result, append);
    }
    return result;
}
