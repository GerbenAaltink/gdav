#pragma once

typedef enum LOGLEVEL {
    LOGLEVEL_ERROR = 0,
    LOGLEVEL_INFO = 1,
    LOGLEVEL_DEBUG = 2
} LOGLEVEL;

int loglevel;

void set_log_level(LOGLEVEL value);

void log_none(const char* fmt, ...);

void log_error(const char* fmt, ...);

void log_info(const char* fmt, ...);

void log_debug(const char* fmt, ...);

#define LOG_ERROR log_error

#ifdef DEBUG
#define LOG_DEBUG log_debug
#else
#define LOG_DEBUG log_debug
#endif

#ifndef ERROR
#define LOG_INFO log_info
#else
#define LOG_INFO log_debug
#endif
