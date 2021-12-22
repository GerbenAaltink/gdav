
#include "sockets.h"
#include "malloc.h"
#include <netinet/tcp.h>

extern Client* clients;
extern int connection_count;

int shield(int val)
{
    if (val != 0) {
        LOG_ERROR("SOCKET ERROR %d\n", GETSOCKETERRNO);
        exit(1);
    }
    return val;
}

SOCKET create_socket(const char* host, const char* port)
{
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags |= AI_PASSIVE;

    struct addrinfo* bind_address;
    getaddrinfo(host, port, &hints, &bind_address);

    SOCKET socket_listen;
    socket_listen = socket(bind_address->ai_family, bind_address->ai_socktype,
        bind_address->ai_protocol);
    if (!ISVALIDSOCKET(socket_listen)) {
        LOG_ERROR("Socket error: %s\n", strerror(errno));
        exit(1);
    }
    int reuse = 1;
    setsockopt(socket_listen, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
    
    if (bind(socket_listen, bind_address->ai_addr, bind_address->ai_addrlen)) {
        LOG_ERROR("Bind error: %s\n", strerror(errno));
        exit(1);
    }
    freeaddrinfo(bind_address);

    if (listen(socket_listen, SOCKET_LISTEN) < 0) {
        LOG_ERROR("Listen error: %d\n", strerror(errno));
        exit(1);
    }

    return socket_listen;
}

int receive(Client* client, char* buff, size_t buffSize)
{
    int bytesReceived = recv(client->socket, buff, buffSize, 0);
    if (LOG_RECV)
        LOG_DEBUG("recv (%d): '%s'\n", bytesReceived, buff);
    if (bytesReceived < 0) {
        LOG_ERROR("Receive error: %d %s\n", errno, strerror(errno));
    } else {
        client->bytesReceived = client->bytesReceived + bytesReceived;
    }

    stats.bytesReceived += bytesReceived;
    return bytesReceived;
}

int sendAll(Client* client, char* data)
{
    size_t toSend = strlen(data);
    size_t sent = 0;

    while (sent != toSend) {
        size_t chunkSize = send(client->socket, data + sent, toSend - sent, 0);
        if (chunkSize < 1) {
            LOG_ERROR("sendAll error: %s\n", strerror(errno));
            return chunkSize;
        }

        if (LOG_SEND)
            LOG_DEBUG("send (%zu/%zu): '%s'\n", sent, toSend, data + sent);

        sent += chunkSize;
        client->bytesSent += chunkSize;
    }
    stats.bytesSent += sent;
    return sent;
}
int sendAllN(Client* client, char* data, size_t toSend)
{
    size_t sent = 0;

    while (sent < toSend) {
        size_t chunkSize = send(client->socket, data + sent, toSend - sent, 0);

        if (chunkSize < 1) {
            LOG_ERROR("sendAll error: %s\n", strerror(errno));
            return chunkSize;
        }

        if (LOG_SEND)
            LOG_DEBUG("send (%zu/%zu): '%s'\n", sent, toSend, data + sent);

        sent += chunkSize;
        client->bytesSent += chunkSize;
    }
    stats.bytesSent += sent;
    return sent;
}

void resetProgress(Progress* progress)
{
    progress->busy = 0;
    progress->size = 0;
}

void resetClient(Client* client)
{
    client->buffer[0] = 0;
    resetProgress(client->progress);
    resetRequest(client->request);
}

Client* get_client(SOCKET s)
{
    struct client_info* ci = clients;
    while (ci) {
        if (ci->socket == s)
            break;
        ci = ci->next;
    }
    if (ci)
        return ci;

    struct client_info* n = (struct client_info*)calloc(1, sizeof(struct client_info));
    n->progress = (Progress*)calloc(1, sizeof(Progress));
    n->progress->busy = 0;
    n->progress->size = 0;
    n->received = 0;
    n->buffer = (char*)calloc(sizeof(char), REQUEST_MAX_LENGTH + 1);
    n->buffer[0] = 0;
    n->writeCount = 0;
    n->readCount = 0;
    n->request = (Request*)calloc(1, sizeof(Request));

    if (!n) {
        LOG_ERROR("Out of memory\n");
        exit(1);
    }
    n->address_length = sizeof(n->address);
    n->next = clients;
    clients = n;
    return n;
}

const char* get_client_address(struct client_info* ci)
{
    static char address_buffer[100];
    getnameinfo((struct sockaddr*)&ci->address, ci->address_length,
        address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
    return address_buffer;
}

Client* accept_client(SOCKET socket)
{
    Client* client = get_client(-1);

    client->address_length = sizeof(struct sockaddr);
    client->socket = accept(socket, (struct sockaddr*)&client->address,
        &client->address_length);
    
    connection_count++;
    sprintf(client->name, "#%d %s", client->socket, get_client_address(client));
    LOG_DEBUG("Accepted: %s Count: %d\n", client->name, connection_count);
    stats.connectionCount += 1;
    if (stats.connectionCount > stats.connectionCountMax)
        stats.connectionCountMax = stats.connectionCount;
    client->reading = true;
    client->writing = true;
    return client;
}

void drop_client(struct client_info* client)
{
    CLOSESOCKET(client->socket);
    struct client_info** p = &clients;
    while (*p) {
        if (*p == client) {
            LOG_DEBUG("Closed: %s Count: %d\n", client->name, connection_count);
            if (LOG_STATS)
                LOG_INFO("%s\n", strstat(stats));
            free(client->request);
            free(client->progress);
            free(client->buffer);
            *p = client->next;
            free(client);
            stats.connectionCount -= 1;
            connection_count -= 1;
            return;
        }
        p = &(*p)->next;
    }
}

struct select_result* wait_on_clients(SOCKET server)
{
    struct select_result* result = (select_result*)malloc(sizeof(select_result));

    FD_ZERO(&result->readers);
    FD_ZERO(&result->writers);
    FD_ZERO(&result->errors);
    FD_SET(server, &result->readers);

    SOCKET max_socket = server;

    struct client_info* ci = clients;
    while (ci) {
        //if(ci->reading)
            FD_SET(ci->socket, &result->readers);
        //if(ci->writing)
            FD_SET(ci->socket, &result->writers);
        FD_SET(ci->socket, &result->errors);
        if (ci->socket > max_socket)
            max_socket = ci->socket;
        ci = ci->next;
    }
    if (select(max_socket + 1, &result->readers, &result->writers,
            &result->errors, 0)
        < 0) {
        fprintf(stderr, "Select failed: %d\n", GETSOCKETERRNO);
        exit(1);
    }
    return result;
}

char* recv_until(int fd, char* needle)
{
    char* buffer = malloc(4096);
    while (true) {
        char buff[2];
        recv(fd, buff, 1, 0);
        strcat(buffer, buff);
        if (strlen(buffer) < 4)
            continue;
        char* last = buffer + strlen(buffer) - 4;
        if (strcmp(last, needle) == 0) {
            return buffer;
        }
    }
}
