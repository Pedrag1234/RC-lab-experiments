#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "../../lib/types.h"
#include "../../lib/utils/utils.h"
#include "../connection/connection.h"

/**
 * @brief Logins into FTP server
 * 
 * @param socket_fd Socket to send info
 * @param user_info Contains user name and password
 * 
 * @return int 0 if success
 */
int auth_login(const int socket_fd, user_info *user_info);

/**
 * @brief Validate the response received 
 * 
 * @param res Response receive
 * @param code Code expected
 * 
 * @return int 0 if success -1 if not
 */
int auth_validate(char *res, const res_t code);

/**
 * @brief Reads the welcome message from FTP server
 * 
 * @param socket_fd Socket to read from
 */
void auth_welcome(const int socket_fd);

/**
 * @brief Sends a request to FTP server, reads response and validates response
 * 
 * @param user_info not used
 * @param cmd The command to send
 * @param cmd_len Length of the command
 * @param req_type Type of response expected
 * @param socket_fd Socket to send command and read response
 * 
 * @return char* returns response
 */
char *auth_request(user_info *user_info, const char *cmd, const size_t cmd_len, const res_t req_type, const int socket_fd);
