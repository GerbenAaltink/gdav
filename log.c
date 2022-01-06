#include <stdarg.h>
#include <stdio.h>
#include "utlist.h"
#include "log.h"
#include <stddef.h>
#include <unistd.h>
#include "malloc.h"
#include <stdbool.h>

extern int loglevel;
extern char log_prefix[10000];
extern LogLine * log_lines;

char log_line_buffer[1024*1024];

int log_line_count = 0;

void log_set_prefix(char * prefix){
    strcpy(log_prefix, !(prefix) ? "" : prefix);
}

bool log_match_true(LogLine * a, LogLine * b) {
    return 0;
}
bool log_match_last(LogLine * a, LogLine * b) {
    return !a->next && !b->next;
}
bool log_match_first(LogLine * a, LogLine * b) {
    return !a->prev && !b->prev;
}

LogLine * log_get_first_line(){
    LogLine * result;
    LogLine filter;
    DL_SEARCH(log_lines, result, &filter, log_match_first);
    return result;
}

bool log_delete_first_line(){
    LogLine * first = log_get_first_line();
    if(!first)
        return false;
    DL_DELETE(log_lines, first);
    log_line_count--;
    return true;
}

void log_add_line(LOGLEVEL level, char * line) {
    LogLine * log_line = malloc(sizeof(LogLine));
    log_line->level = level;
    strncpy(log_line->line, line, LOG_LINE_LENGTH - 1);
    DL_APPEND(log_lines, log_line);
    log_line_count++;
    if(log_line_count > LOG_MAX_HISTORY)
        log_delete_first_line();
}


LogLine * log_tail(int size) {
    LogLine filter;
    LogLine * result;
    filter.next = NULL;
    DL_SEARCH(log_lines, result, &filter, log_match_last);
    if(!result)
        return result;
    while(size != 0)
    {
        if(result->prev)
            result = result->prev;
        size--;
    }
    return result;
}

void log_write_prefix(char * level_string){
    if(log_prefix)
         printf("%s:%s %s ", level_string, strlen(level_string) == 4 ? " " : "", log_prefix);
    else
        printf("%s:%s ", level_string, strlen(level_string) == 4 ? " " : "");
}
void log_write_suffix(char * fmt) {
    if(fmt[0] != 0 && fmt[strlen(fmt) -1] != '\n')
        printf("\n");
}

void set_log_level(LOGLEVEL value) { loglevel = value; }

void log_none(const char* fmt, ...) { }

char * log_to_string(const char * fmt, ...) {
    static char result[4096];
    va_list args;
    va_start(args, fmt);
    vsprintf(result, fmt, args);
    va_end(args);
    return result;
}

void log_error(const char* fmt, ...)
{   
    log_write_prefix("ERROR");
    va_list args;
    va_start(args, fmt);
    vsprintf(log_line_buffer, fmt, args);
    printf(log_line_buffer);
    log_add_line(2, log_line_buffer);
    va_end(args);
    log_write_suffix(fmt);
}

void log_info(const char* fmt, ...)
{
    if (loglevel < 1)
        return;

    log_write_prefix("INFO");
    va_list args;
    va_start(args, fmt);
    
   // vprintf(fmt, args);
    vsprintf(log_line_buffer, fmt, args);
    printf(log_line_buffer);
    log_add_line(1, log_line_buffer);
    va_end(args);
    log_write_suffix(fmt);
}

void log_debug(const char* fmt, ...)
{
    if (loglevel < 2)
        return;
    log_write_prefix("DEBUG");
    va_list args;
    va_start(args, fmt);

    vsprintf(log_line_buffer, fmt, args);
    printf(log_line_buffer);
    log_add_line(2, log_line_buffer);
    va_end(args);
    log_write_suffix(fmt);
}

void log_unload(){
    LogLine * log_line;
    LL_FOREACH(log_lines, log_line) LL_DELETE(log_lines, log_line);
}