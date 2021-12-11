#pragma once

#include "sockets.h"

typedef enum HTTP_STATUS {
    HTTP_OK = 1,
    HTTP_ERROR = 2,
    HTTP_BUSY = 0
} HTTP_STATUS;

HTTP_STATUS http_status_response(Client* client, int status, char* message,
    char* body);
HTTP_STATUS http_response_201(Client* client);
HTTP_STATUS http_response_404(Client* client);
HTTP_STATUS http_html_index(Client* client);
HTTP_STATUS http_options(struct client_info* client);
HTTP_STATUS http_mkcol(Client* client);
HTTP_STATUS http_head(Client* client);
HTTP_STATUS http_delete(struct client_info* client);
int drain(Client* client);
HTTP_STATUS http_put(struct client_info* client);
char* join_path(char* pDirectory, char* pName);
bool valid_path(char* pName);
int http_propfind(struct client_info* client);
HTTP_STATUS http_route_get(Client* client);