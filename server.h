#pragma once

#include "sockets.h"

void handle_write(Client* client);
int handle_read(Client* client);
int serve(const char* host, const char* port);