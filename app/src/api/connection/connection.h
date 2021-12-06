#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../../lib/types.h"

int init_connection(user_info * user_info);

int send_req();

int test_SendMsg();

int read_rep();

int close_connection();