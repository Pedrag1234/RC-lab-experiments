#include "pasv.h"

int pasv_get_client_info(client_info *client_info, const char *res)
{
  sscanf(
    res,
    "(%d,%d,%d,%d,%d,%d)",
    &client_info->ip1,
    &client_info->ip2,
    &client_info->ip3,
    &client_info->ip4,
    &client_info->port1,
    &client_info->port2
  );

  return 0;
}

int pasv_get_client_ip(char *client_ip, const client_info *client_info)
{
  sprintf(
    client_ip, 
    "%d.%d.%d.%d", 
    client_info->ip1, 
    client_info->ip2,
    client_info->ip3,
    client_info->ip4
  );

  return 0;
}

int pasv_get_client_port(const client_info * client_info)
{
  return client_info->port1 * 256 + client_info->port2;
}

int pasv_connect(user_info *user_info, int server_fd, char *client_ip)
{
  client_info client_info;

  auth_login(server_fd, user_info);

  char *res = strchr(auth_request(user_info, PASV_CMD, strlen(PASV_CMD), PASSIVE_MODE, server_fd), '(');

  pasv_get_client_info(&client_info, res);
  pasv_get_client_ip(client_ip, &client_info);
  int client_port = pasv_get_client_port(&client_info);

  printf("\npasv.info.connected: {client_ip: %s, client_port: %d}\n", client_ip, client_port);

  return client_port;
}

int pasv_retr(const int socket_fd, const user_info *user_info)
{
  char file_cmd[BUFFER_SIZE];

  if (user_info->path == NULL)
    return -1;

  auth_request(user_info, TYPE_CMD, strlen(TYPE_CMD), CONFIRM, socket_fd);

  sprintf(file_cmd, "RETR %s\r\n", user_info->path);

  auth_request(user_info, file_cmd, strlen(file_cmd), NOOP, socket_fd);

  return 0;
}

int pasv_download(user_info *user_info)
{
  char client_ip[16];

  int server_fd = init_connection(user_info->ip, user_info->port);
  
  int client_port = pasv_connect(user_info, server_fd, client_ip);

  int data_fd = init_connection(client_ip, client_port);

  if (pasv_retr(server_fd, user_info) < 0) {
    perror("passive.error.retrieve_file");
    exit(-1);
  }

  FILE *fp = fopen(user_info->f_name, "w");

  if(fp == NULL ){
    perror("passive.error.open_file");
    exit(-1);
  }

  printf("\npassive.info.download_started\n");

  char buffer[FILE_BUFFER_SIZE];
  int i = 0;

  while (true) {
    ++i;

    int bytes = read(data_fd, buffer, FILE_BUFFER_SIZE);
    if (bytes == 0) break;

    fwrite(buffer, bytes, 1, fp);
  }

  fclose(fp);

  printf("\npassive.info.download_ended\n");

  return 0;
}