#include <stdbool.h>

#include "server.h"
#include "http.h"
#include "log.h"

void handle_write(Client* client)
{
    int close = 2;

    if (client->request->isGet) {
        close = http_route_get(client);
    }
    if (client->request->isPropfind) {
        close = http_propfind(client);
    }
    if (client->request->isOptions) {
        close = http_options(client);
    }
    if (client->request->isDelete) {
        close = http_delete(client);
    }
    if (client->request->isHead) {
        close = http_head(client);
    }
    if (client->request->isPut) {
        close = http_put(client);
    }
    if (client->request->isMkcol) {
        close = http_mkcol(client);
    }
    LOG_DEBUG("Done %d %s %s %s\n", close, client->request->method,
        client->request->path, client->name);
            
    client->request->bytesLeft = 0;
    if (close == 0) {
        client->progress->busy = true;
    } else if (close == 1 && client->request->keepAlive) {
        resetClient(client);
        client->received = 0;
    } else if (close) {
        drop_client(client);
    }
}

int handle_read(Client* client)
{
    
    int buffSize = SOCKET_READ_BUFFER_SIZE;
    if (client->progress->busy == true) {
        if(client->request->contentLength - client->progress->size < SOCKET_READ_BUFFER_SIZE)
            buffSize = client->request->contentLength - client->progress->size;
    }
    char data[buffSize + 1];
    
    //bzero(data, buffSize + 1);
    LOG_DEBUG("Reading: %s\n", client->name);
    int recvLength = receive(
        client, data, buffSize); // recv(client->socket, data, sizeof(data), 0);
    LOG_DEBUG("Received: %d bytes from %s\n", recvLength, client->name);
    if (recvLength < 1) {
        return recvLength;
    }
    data[recvLength] = 0;
    
    client->received += recvLength; 
    if (client->progress->busy == 0) {
        strcat(client->buffer, data);
        if (str_index(client->buffer, "\r\n\r\n") != -1) {
            client->request = parseRequest(client->buffer);
            client->hasRequest = true;
            LOG_INFO("%s %s %s\n", client->request->method, client->request->path,
                client->name);
            client->progress->busy = 1;
            bzero(client->buffer, sizeof(client->buffer));
            
            client->request->bytesLeft = recvLength - strlen(client->request->headers);           
            if (client->request->isPropfind) {
                drain(client);
            }

        }
    } else {
        strcpy(client->request->body, data);
        client->request->bytesLeft = recvLength;
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
            if (!ISVALIDSOCKET(client->socket)) {
                LOG_ERROR("Accept error: %d\n", GETSOCKETERRNO);
                return 1;
            }
            LOG_INFO("Connected: %s\n", client->name);
        }
        Client * client = clients;
        while (client) {
            Client * next = client->next;
            if (FD_ISSET(client->socket, &selected->errors)) {
                drop_client(client);
                client = next;
                continue;
            }
            if (FD_ISSET(client->socket, &selected->readers)) {
                bool success = handle_read(client) > 0;
                if (!success) {
                    drop_client(client);
                    client = next;
                    continue;
                }
            }
            
            if (client->progress->busy == true && FD_ISSET(client->socket, &selected->writers)) {
                handle_write(client);
            }

               
            

            
            client = next;
        }
        free(selected);
    }
}