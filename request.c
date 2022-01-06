#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base64.h"
#include <stdbool.h>

#include "log.h"
#include "request.h"
#include "url.h"
#include "user.h"
#include "functions.h"
#include "http_method.h"
#include "malloc.h"

char* safe_strstr(char* pdata, char* needle)
{
    char* data = pdata;
    return strstr(data, needle);
}

int str_index(char* data, char* needle)
{
    char* left = safe_strstr(data, needle);
    if (!left)
        return -1;
    int result = strlen(data) - strlen(left);
    return result;
}

bool str_contains(char * data, char * needle){
    return str_index(data, needle) != -1;
}
bool str_startswith(char * data, char * needle) {
    return str_index(data, needle) == 0;
}

bool str_bool(char * data){
    return str_startswith(data, "T") || str_startswith(data, "t") || str_startswith(data,"Y") || str_startswith(data, "y") || streq(data,"1");
}

char * str_strip_url(char * str) {
    char * data = str;
    data += str_index(data, "/") + 1;
    data += str_index(data, "/") + 1;
    data += str_index(data, "/");
    strcpy(str, data);
    return str;
}

void getHeaders(char* data, char* result)
{
    int index = str_index(data, "\r\n\r\n");
    strncpy(result, data, index + 4);
    result[index + 4] = 0;
}

void getHeaderValue(char* pheaders, char* name, char* result)
{
    // strcpy(headers, "\r\n");
    char* found = safe_strstr(pheaders, name);

    if (found == 0) {
        strcpy(result, "");
        return;
    }
    found = found + strlen(name) + 2;
    int index = str_index(found, "\r\n");
    if (index != -1) {
        strncpy(result, found, index);
        result[index] = 0;
        return;
    }
    strcpy(result, "");
    ///strcpy(result, found);
    ///result[strlen(found)] = 0;
}

int get_header_int(char * pheaders, char * name, int default_value) {
    char * result[100];
    getHeaderValue(pheaders, name, result);
    if(!strlen(result))
        return default_value;
    return atoi(result);
}
size_t get_header_size(char * pheaders, char * name, size_t default_value) {
    char * result[100];
    getHeaderValue(pheaders, name, result);
    if(!strlen(result))
        return default_value;
    return atoll(result);
}
bool get_header_bool(char * pheaders, char * name, bool default_value) {
    char * result[10];
    getHeaderValue(pheaders, name, result);
    if(!strlen(result))
        return default_value;
    return str_bool(result);
}
char * get_header_string(char * pheaders, char * name, char * default_value) {
    static char * result[4096];
    czero(result);
    getHeaderValue(pheaders, name, result);
    if(!strlen(result))
        return default_value;
    return result;
}

void dumpRequest(Request* request)
{
    printf("Method: %s\n", request->method);
    printf("Path: %s\n", request->path);
    printf("Relative path: %s\n", request->relativePath);
    printf("Version: %s\n", request->version);
    printf("Headers: %s\n", request->headers);
    printf("isGet: %d\n", request->isGet);
    printf("isPropfind: %d\n", request->isPropfind);
    printf("isOptions: %d\n", request->isOptions);
    printf("isPut: %d\n", request->isPut);
    printf("User-Agent: %s\n", request->userAgent);
    printf("Depth: %s\n", request->depth);
    printf("Content-Length: %zu\n", request->contentLength);
    printf("Body: %s\n", request->body);
}

void resetRequest(Request* request)
{
    bzero(request, sizeof(Request));
    strcpy(request->username, "anonymous");
    strcpy(request->password, "password");
    strcpy(request->root, ".");
    request->authorized = false;
    request->bytesLeft = 0;
    request->contentLength = 0;
    strcpy(request->body, "");
    strcpy(request->headers, "");
    return;
}

Request * request_init() {
    Request * request = (Request *)httpc_malloc(sizeof(Request));
    resetRequest(request);
    return request;
}

void parseAuthorization(Request * request){
    
    if(!strlen(request->authorization))
    {
        strcpy(request->username, "anonymous");
        strcpy(request->password, "anonymous");
        strcpy(request->root, ".");
        request->authorized = false;
        return;
    }
    char * auth_header = malloc(strlen(request->authorization) + 1);
    strcpy(auth_header, request->authorization);
    auth_header = strstr(auth_header," ") + 1;
    
    size_t olen;
    size_t ilen = strlen(auth_header);
    
    char * credentials = (char *)base64_decode(auth_header, ilen, &olen);
    credentials[olen] = 0;
    LOG_DEBUG("Auth: %s\n", credentials);
    char seperator[] = ":";
    if(strlen(credentials))
        strcpy(request->username, strtok(credentials, seperator));
    if(strlen(credentials))
        strcpy(request->password, strtok(NULL, seperator));
    free(credentials);
    User * user = user_get(request->username);
    if(user && !strcmp(user->password, request->password)){
        request->authorized = true;
        strcpy(request->root, user->root);
    }else{
        request->authorized = false;
        strcpy(request->root, ".");
    }

}

Request* parseRequest(int received, char* data, Request* request)
{
    bzero(request, sizeof(Request));
    const char* token = " ";

    strcpy(request->root, ".");
    request->authorized = false;

    getHeaders(data, request->headers);
    
    getHeaderValue(request->headers, "Authorization", request->authorization);
    if(!strlen(request->authorization))
        getHeaderValue(request->headers,"Proxy-Authorization", request->authorization);
    parseAuthorization(request);

    char tokenizeData[strlen(data) + 1];
    strcpy(tokenizeData, data);

    LOG_DEBUG("Parsing headers\n");
    strcpy(request->method_str, strtok(tokenizeData, token));
    LOG_DEBUG("Parsing headers\n");

    request->method = http_method_from_str(request->method_str);

    LOG_DEBUG("Parsing headers\n");
    strcpy(request->path, url_decode(strtok(NULL, token)));
    strcpy(request->relativePath, request->path + 1);
    strcpy(request->realPath, request->root);
    strcat(request->realPath, request->path);
    strtrimr(request->realPath, '/');
    strcpy(request->version, strtok(NULL, "\r\n"));
    sprintf(request->repr, "%s %s %s", request->method_str, request->username, request->path);
    LOG_DEBUG("Parsed request line: %s\n", request->repr);
    
    char* body = safe_strstr(data, "\r\n\r\n");

    if (str_index(body, "\r\n\r\n") != -1) {
        memcpy(request->body, body + 4, received - strlen(request->headers));
        request->bytesLeft = received - strlen(request->headers);
        LOG_DEBUG("Body size: %zu\n", request->bytesLeft);
    }else{
        LOG_DEBUG("No body\n", request->repr);
    }
    
    //BUGG!: request->bytesLeft = strlen(request->body);
    /*
    request->isGet = strncmp(request->method, "GET", 3) == 0;
    request->isPropfind = strncmp(request->method, "PROPFIND", 8) == 0;
    request->isOptions = strncmp(request->method, "OPTIONS", 7) == 0;
    request->isPut = strncmp(request->method, "PUT", 3) == 0;
    request->isDelete = strncmp(request->method, "DELETE", 6) == 0;
    request->isHead = strncmp(request->method, "HEAD", 4) == 0;
    request->isMkcol = strncmp(request->method, "MKCOL", 5) == 0;
    request->isLock = strncmp(request->method, "LOCK", 4) == 0;
    request->isUnlock = strncmp(request->method, "UNLOCK", 6) == 0;*/

    getHeaderValue(request->headers, "Range", request->range);
    request->is_range = strlen(request->range) > 0;
    if (request->is_range) {
        LOG_DEBUG("Ranged: %s\n", request->range);
        sscanf(request->range, "bytes=%zu-%zu", &request->range_start, &request->range_end);
        // Weghalen -> TESTEN
        //if (request->range_end == 1)
          //  request->range_end = 0;
    }

    //request->depth = get_header_
    //getHeaderValue(request->headers, "Depth", request->depth);

    request->depth = get_header_int(request->headers, "Depth", 0);

    getHeaderValue(request->headers, "User-Agent", request->userAgent);

    request->contentLength = get_header_size(request->headers, "Content-Length", 0L);
    //getHeaderValue(request->headers, "Content-Length", contentLength);
    //request->contentLength = atoll(contentLength);
    char headerValue[4096];

    getHeaderValue(request->headers, "Connection", request->connection);

    request->keepAlive = str_contains(request->connection, "Keep-Alive") || str_contains(request->connection, "TE");
    request->overwrite = get_header_bool(request->headers, "Overwrite", false);

    getHeaderValue(request->headers, "Destination", czero(headerValue));
    if(strlen(headerValue)){
        if(str_index(headerValue, "http") == 0){
            str_strip_url(headerValue);
        }
        strcpy(request->destination, url_decode(headerValue));
        strcpy(request->realDestination, request->root);
        strcat(request->realDestination, request->destination);
    }
    getHeaderValue(request->headers, "Lock-Token", request->lockToken);
    

    LOG_DEBUG("Parsed headers\n");

    return request;
}
