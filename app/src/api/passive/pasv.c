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

int pasv_download(user_info *user_info)
{
  client_info client_info;

  char client_ip[16];
  int client_port;
  int server_fd = init_connection(user_info);

  auth_login(server_fd, user_info);

  char *res = strchr(auth_request(user_info, PASV_CMD, strlen(PASV_CMD), PASSIVE_MODE, server_fd), '(');

  pasv_get_client_info(&client_info, res);
  pasv_get_client_ip(client_ip, &client_info);
  client_port = pasv_get_client_port(&client_info);

  printf("\npasv.info.connected: {client_ip: %s, client_port: %d}\n", client_ip, client_port);



  return 0;
}