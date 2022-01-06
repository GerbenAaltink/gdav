#pragma once

#define LOG_LINE_LENGTH 200
#define LOG_MAX_HISTORY 1000

typedef enum LOGLEVEL {
    LOGLEVEL_ERROR = 0,
    LOGLEVEL_INFO = 1,
    LOGLEVEL_DEBUG = 2
} LOGLEVEL;

typedef struct LogLine {
    LOGLEVEL level;
    char line[LOG_LINE_LENGTH];
    struct LogLine * next;
    struct LogLine * prev;
} LogLine;

LogLine * log_lines;

int loglevel;

char log_prefix[10000];

void log_add_line(LOGLEVEL level, char * line);

void log_set_prefix(char * prefix);

void set_log_level(LOGLEVEL value);

void log_none(const char* fmt, ...);

void log_error(const char* fmt, ...);

void log_info(const char* fmt, ...);

void log_debug(const char* fmt, ...);

void log_unload();

LogLine * log_tail(int size);

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
