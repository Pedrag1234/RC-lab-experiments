#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "../../lib/types.h"

/**
 * @brief Creates a socket with the specified ip and port
 * 
 * @param ip Specified Ip
 * @param port Specified Port
 * 
 * @return int socket descriptor if success
 */
int init_connection(char *ip, int port);

/**
 * @brief Sends a command through socket 
 * 
 * @param cmd The command to send
 * @param cmd_len Lenght of the command to send
 * @param socket_fd The socket to send the command through
 * 
 * @return int 0 if success -1 if not
 */
int send_req(const char * cmd, const size_t cmd_len, const int socket_fd);

/**
 * @brief Reads response after send command
 * 
 * @param socket_fd Socket to read the response from
 * @param res Response received
 * 
 * @return int 0 if success -1 if not
 */
int read_res(const int socket_fd, char *res);

/**
 * @brief Closes a connection
 * 
 * @return int 0 if success -1 if not
 */
int close_connection();