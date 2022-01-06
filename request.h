#pragma once
#include "config.h"
#include <stdbool.h>
#include <stdlib.h>
#include "http_method.h"

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
    HTTP_METHOD method;
    char path[4096];
    char relativePath[4096];
    char realPath[4096];
    char root[4096];
    char username[256];
    char password[256];
    bool authorized;
    char version[10];
    char headers[4096];
    int depth;
    char userAgent[1024];
    char authorization[1024];
    char lockToken[64];
    bool isGet;
    bool isPropfind;
    bool isOptions;
    bool isPut;
    bool isDelete;
    bool isMkcol;
    bool isHead;
    bool isLock;
    bool isUnlock;
    bool keepAlive;
    char connection[100];
    RequestMethod route;
    size_t contentLength;
    char body[REQUEST_MAX_LENGTH];
    long bytesLeft;
    size_t bodyReceived;
    size_t range_start;
    size_t range_end;
    char range[100];
    bool is_range;
    bool overwrite;
    char destination[4096];
    char realDestination[4096];
    char method_str[10];
    char repr[4096];

} Request;

char* safe_strstr(char* pdata, char* needle);
int str_index(char* data, char* needle);
void getHeaders(char* data, char* result);
void getHeaderValue(char* pheaders, char* name, char* result);
Request * request_init();
void dumpRequest(Request* request);
void resetRequest(Request* request);
Request* parseRequest(int received, char* data, Request* request);
