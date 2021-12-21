#include "auth.h"

void auth_login(int fdsocket, char *username, char *password)
{
  if (username == NULL || password == NULL) {
    perror("Invalid username or password");
    exit(-1);
  }

  printf("\nUsername: %s\n", username);

  int CMD_LENGTH = strlen(username) + 8;
  char usr_cmd[CMD_LENGTH];
  sprintf(usr_cmd, "USER %s\r\n", username);
  
}