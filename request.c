#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "request.h"
#include "url.h"

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
    printf("Content-Length: %d\n", request->contentLength);
    printf("Body: %s\n", request->body);
}

void resetRequest(Request* request)
{
    free(request);
    request = (Request*)malloc(sizeof(Request));
    return;
}

Request* parseRequest(char* data)
{
    Request* request = malloc(sizeof(Request));
    const char* token = " ";

    int received = strlen(data);

    printf("-1\n");
    getHeaders(data, request->headers);
    
    printf("0\n");
    char tokenizeData[strlen(data) + 1];
    strcpy(tokenizeData, data);

    strcpy(request->method, strtok(tokenizeData, token));
    strcpy(request->path, url_decode(strtok(NULL, token)));
    strcpy(request->relativePath, request->path + 1);
    strcpy(request->version, strtok(NULL, "\r\n"));
    printf("1\n");
    char* body = safe_strstr(data, "\r\n\r\n");
    
    printf("2\n");
    if (str_index(body, "\r\n\r\n") != -1) {
        strcpy(request->body, body + 4);
        
    }

    printf("3\n");
    request->bytesLeft = request->body != 0 ? strlen(request->body) : 0;

    request->isGet = strncmp(request->method, "GET", 3) == 0;
    request->isPropfind = strncmp(request->method, "PROPFIND", 8) == 0;
    request->isOptions = strncmp(request->method, "OPTIONS", 7) == 0;
    request->isPut = strncmp(request->method, "PUT", 3) == 0;
    request->isDelete = strncmp(request->method, "DELETE", 6) == 0;
    request->isHead = strncmp(request->method, "HEAD", 4) == 0;
    request->isMkcol = strncmp(request->method, "MKCOL", 5) == 0;
   
    
    printf("4\n");
    getHeaderValue(request->headers, "Range", request->range);
    request->is_range = strlen(request->range) > 0;
    if(request->is_range){
        sscanf(request->range, "bytes=%zu-%zu", &request->range_start, &request->range_end);
        if(request->range_end == 1)
            request->range_end = 0;
    }
    
    getHeaderValue(request->headers, "Depth", request->depth);

    getHeaderValue(request->headers, "User-Agent", request->userAgent);
    char contentLength[1024];

    getHeaderValue(request->headers, "Content-Length", contentLength);
    request->contentLength = atoll(contentLength);

    char connectionHeader[64];
    getHeaderValue(request->headers, "Connection", connectionHeader);
    request->keepAlive = strncmp(connectionHeader, "Keep-Alive", 10) == 0;

    return request;
}
