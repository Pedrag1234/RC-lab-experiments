#pragma once

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>


#include "../types.h"

int argsParser(char * params, user_info * user_info);

int getIp(user_info * user_info);

int getFileName(user_info * user_info);