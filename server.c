#include <stdbool.h>
#include "stats.h"
#include "sockets.h"
#include "http.h"
#include "log.h"
#include "server.h"
#include "user.h"
#include "http_method.h"

HTTP_STATUS http_route(Client * client){
    switch(client->request->method) {
            case HTTP_METHOD_LOCK:
                return http_lock(client);
            case HTTP_METHOD_UNLOCK:
                return http_unlock(client);
            case HTTP_METHOD_GET:
                return http_route_get(client);
            case HTTP_METHOD_PROPFIND:
                return http_propfind(client);
            case HTTP_METHOD_OPTIONS:
                return http_options(client);
            case HTTP_METHOD_DELETE:
                return http_delete(client);
            case HTTP_METHOD_HEAD:
                return http_head(client);
            case HTTP_METHOD_PUT:
                return http_put(client);
            case HTTP_METHOD_MKCOL:
                return http_mkcol(client);
            case HTTP_METHOD_MOVE:
                return http_move(client);
    }
    http_status_response(client, "405", "Not Allowed", "HTTP Method is not implemented");
    return HTTP_ERROR;
}

void handle_write(Client* client)
{
    HTTP_STATUS status = HTTP_ERROR;
    
    bool authorization_required = user_count > 0 && !client->request->authorized;

    if(authorization_required)
    {
        status = http_response_401(client);
        LOG_INFO("Authentication failed for %s", client->request->username);
    }else{
        status = http_route(client);   
        if(status == HTTP_BUSY)
            LOG_DEBUG("BUSY");
        else if(status == HTTP_ERROR)
            LOG_ERROR("ERROR");
        else if(status == HTTP_OK)
            LOG_INFO("DONE");
    }


    client->request->bytesLeft = 0;

    if (status == HTTP_BUSY) {
        client->progress->busy = true;
    } else if (status == HTTP_OK && client->request->keepAlive) {
        resetClient(client);
        client->progress->busy = false;
        client->received = 0;
        client->reading = true;
        client->writing = false;
    } else {
        drop_client(client);
    }
    switch(status) {
        case HTTP_OK:
            stats.requestExecuting--;
            stats.requestDone++;
            break;
        case HTTP_ERROR:
            stats.requestExecuting--;
            stats.requestError++;
            break;
        case HTTP_BUSY:
            stats.requestChunks++;
            break;
    }
}

void update_log_prefix(Client * client) {
    char prefix[10000];
    
    strcpy(prefix, client->name);
    strcat(prefix, " ");
    if(client->progress->busy)
        strcat(prefix, client->request->repr);
    else
        strcat(prefix, "READ");
    log_set_prefix(prefix);
}

int handle_read(Client* client)
{
    int buffSize = SOCKET_READ_BUFFER_SIZE;
    if (client->progress->busy == true) {
        if (client->request->contentLength - client->progress->size < SOCKET_READ_BUFFER_SIZE)
            buffSize = client->request->contentLength - client->progress->size;
    }
    char data[buffSize + 1];

    bzero(data, buffSize);

    //bzero(data, buffSize + 1);
    LOG_DEBUG("Reading: %s\n", client->name);
    int recvLength = receive(
        client, data, buffSize); // recv(client->socket, data, sizeof(data), 0);
    LOG_DEBUG("Received: %d bytes from %s\n", recvLength, client->name);
    if (recvLength < 1) {
        return recvLength;
    }
    client->received += recvLength;
    //data[recvLength] = 0;
    
    if (client->progress->busy == 0) {
        strcat(client->buffer, data);
        if (str_index(client->buffer, "\r\n\r\n") != -1) {
            parseRequest(client->received, client->buffer, client->request);
            
            client->hasRequest = true;
            client->progress->busy = 1;

            LOG_INFO("%s %s\n", client->request->repr, client->name);
            bzero(client->buffer, (size_t)sizeof(client->buffer));
            client->received = 0;
            
            //client->request->bytesLeft = recvLength - strlen(client->request->headers);
            if (client->request->method == HTTP_METHOD_PROPFIND) {
                drain(client);
            }
            client->writing = true;
            client->reading = false;
            stats.requestCount++;
            stats.requestExecuting++;
        }else{
            client->writing = false;
        }

    } else {
        memcpy(client->request->body, data, recvLength);
        client->request->bytesLeft = recvLength;
        client->writing = true;
        client->reading = false;
    }

    return recvLength;
}

int serve(const char* host, const char* port)
{
    SOCKET server = create_socket(host, port);
    while (1) {
        select_result* selected = wait_on_clients(server);
        if (FD_ISSET(server, &selected->readers)) {
            Client* client = accept_client(server);
            update_log_prefix(client);
            if (!ISVALIDSOCKET(client->socket)) {
                LOG_ERROR("Accept error: %d\n", GETSOCKETERRNO);
                return 1;
            }
            LOG_INFO("Connected: %s\n", client->name);
        }
        Client* client = clients;
        while (client) {
            Client* next = client->next;
            update_log_prefix(client);
            if (FD_ISSET(client->socket, &selected->errors)) {
                drop_client(client);
                client = next;
                continue;
            }
            if (FD_ISSET(client->socket, &selected->readers)) {
                bool success = handle_read(client) > 0;
                update_log_prefix(client);
                if (!success) {
                    drop_client(client);
                    client = next;
                    continue;
                }
            }
            if (client->progress->busy == true && FD_ISSET(client->socket, &selected->writers)) {
                handle_write(client);
                update_log_prefix(client);
            }

            client = next;
        }
        free(selected);
    }
}
