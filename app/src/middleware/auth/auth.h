#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "../../lib/types.h"
#include "../../lib/utils/utils.h"
#include "../../api/connection/connection.h"

int auth_login(const int socket_fd, user_info *user_info);
int auth_validate(char *res, const res_t code);