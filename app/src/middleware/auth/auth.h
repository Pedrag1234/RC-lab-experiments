#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "../../lib/types.h"
#include "../../lib/utils/utils.h"
#include "../connection/connection.h"

int auth_login(const int socket_fd, user_info *user_info);

int auth_validate(char *res, const res_t code);

void auth_welcome(const int socket_fd);

char *auth_request(user_info *user_info, const char *cmd, const size_t cmd_len, const res_t req_type, const int socket_fd);
