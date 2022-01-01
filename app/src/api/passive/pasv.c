#include "pasv.h"

int pasv_connect(user_info *user_info)
{
  char client_ip[16];
  int client_port;
  int server_fd = init_connection(user_info);

  auth_login(server_fd, user_info);

  strcpy(client_ip, user_info->ip);
  client_port = user_info->port;

  if (client_ip == NULL) {
    perror("pasv.error.client_ip");
    exit(-1);
  }

  auth_request(user_info, PASV_CMD, strlen(PASV_CMD), PASSIVE_MODE, server_fd);
  
}