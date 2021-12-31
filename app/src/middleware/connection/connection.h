#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "../../lib/types.h"

int init_connection(user_info * user_info);

int send_req(const char * cmd, const size_t cmd_len, const int socket_fd);

int read_res(const int socket_fd, char *res);

int close_connection();