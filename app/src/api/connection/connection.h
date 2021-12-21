#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "../../lib/types.h"

int init_connection(user_info * user_info);

int send_req(user_info * user_info, char * command, int size);

int read_rep(user_info * user_info);

int close_connection();