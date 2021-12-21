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

int send_req(user_info * user_info, char * command, size_t size, int socket_fd);

char* read_res(user_info * user_info, int socket_fd);

int close_connection();