#pragma once
#include "config.h"
#include <stdbool.h>
#include <stdlib.h>

typedef enum RequestMethod {
    RM_NONE,
    RM_GET,
    RM_PROPFIND,
    RM_OPTIONS,
    RM_PUT,
    RM_DELETE,
    RM_MKCOL,
    RM_HEAD
} RequestMethod;

typedef struct Request {
    char method[10];
    char path[4097];
    char relativePath[4097];
    char version[10];
    char headers[4096];
    char depth[1024];
    char userAgent[1024];
    bool isGet;
    bool isPropfind;
    bool isOptions;
    bool isPut;
    bool isDelete;
    bool isMkcol;
    bool isHead;
    bool keepAlive;
    RequestMethod route;
    size_t contentLength;
    char body[REQUEST_MAX_LENGTH];
    long bytesLeft;
    size_t bodyReceived;
    size_t range_start;
    size_t range_end;
    char range[100];
    bool is_range;

} Request;

char* safe_strstr(char* pdata, char* needle);
int str_index(char* data, char* needle);
void getHeaders(char* data, char* result);
void getHeaderValue(char* pheaders, char* name, char* result);
void dumpRequest(Request* request);
void resetRequest(Request* request);
Request* parseRequest(int received, char* data, Request* request);
