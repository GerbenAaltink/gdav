#pragma once

#include <stdarg.h>
#include <stdio.h>

#include "log.h"

void set_log_level(LOGLEVEL value) { loglevel = value; }

void log_none(const char* fmt, ...) { }

void log_error(const char* fmt, ...)
{

    printf("ERROR:\t");
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

void log_info(const char* fmt, ...)
{
    if (loglevel < 1)
        return;

    printf("INFO:\t");
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

void log_debug(const char* fmt, ...)
{
    if (loglevel < 2)
        return;
    printf("DEBUG:\t");
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}