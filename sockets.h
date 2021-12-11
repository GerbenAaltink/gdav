#pragma once

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "log.h"
#include "request.h"
#include "stats.h"

#define ISVALIDSOCKET(s) (s >= 0)
#define CLOSESOCKET(s) close(s)
#define SOCKET int
#define GETSOCKETERRNO (errno)

bool LOG_RECV;
bool LOG_SEND;

extern bool LOG_RECV;
extern bool LOG_SEND;

static int connection_count;

int shield(int val);
SOCKET create_socket(const char* host, const char* port);

#define MAX_REQUEST_SIZE 2047

typedef struct Progress {
    char* filename;
    size_t size;
    int busy;
} Progress;


struct client_info {
    socklen_t address_length;
    struct sockaddr_storage address;
    SOCKET socket;
    int received;
    struct client_info* next;
    char sendFilePath[1000];
    char name[32];
    Request* request;
    Progress* progress;
    char* buffer;
    bool hasRequest;
    long bytesSent;
    long bytesReceived;
    size_t bodyReceived;
};

typedef struct client_info Client;

typedef struct select_result {
    fd_set readers;
    fd_set writers;
    fd_set errors;
} select_result;
struct select_result* wait_on_clients(SOCKET server);

Client* clients;

int receive(Client* client, char* buff, size_t buffSize);

int sendAll(Client* client, char* data);
int sendAllN(Client* client, char* data, int toSend);

void resetProgress(Progress* progress);

void resetClient(Client* client);

Client* get_client(SOCKET s);
const char* get_client_address(struct client_info* ci);
Client* accept_client(socket);
void drop_client(struct client_info* client);
fd_set wait_on_writables(SOCKET server);
char* recv_until(int fd, char* needle);
