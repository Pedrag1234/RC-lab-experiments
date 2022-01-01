#pragma once

#include "../../middleware/auth/auth.h";
#include "../../middleware/connection/connection.h";

int pasv_get_client_info(client_info *client_info, const char *res);

int pasv_get_client_ip(char *client_ip, const client_info *client_info);

int pasv_get_client_port(const client_info * client_info);

int pasv_connect(user_info *user_info, int server_fd, char *client_ip);

int pasv_retr(const int socket_fd, const user_info *user_info);

int pasv_download(user_info *user_info);