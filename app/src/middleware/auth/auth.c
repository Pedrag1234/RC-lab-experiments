#include "auth.h"

int auth_validate(char *res, const res_t code)
{
  printf('\nauth_validate.1\n');

  char *code_str = my_itoa(code);

  printf('\nauth_validate.2\n');

  if (strncmp(res, code_str, strlen(code_str)) != 0)
    return -1;

  return 0;
}

int auth_login(const int socket_fd, user_info *user_info)
{
  if (user_info->usr == NULL || user_info->pwd == NULL) {
    perror("auth.error.missing_credentials");
    exit(-1);
  }

  printf("\nUsername: %s\n", user_info->usr);

  const size_t USR_CMD_LENGTH = strlen(user_info->usr) + 8;
  const size_t PWD_CMD_LENGTH = strlen(user_info->pwd) + 8;

  char usr_cmd[BUFFER_SIZE];
  char pwd_cmd[BUFFER_SIZE];
  char *res;
  int size_res;

  sprintf(usr_cmd, "user %s\r\n", user_info->usr);
  sprintf(pwd_cmd, "pass %s\r\n", user_info->pwd);
  
  if (send_req(user_info, usr_cmd, USR_CMD_LENGTH, socket_fd) < 0 ){
    perror("auth.error.bad_request");
    exit(-1);
  }

  res = read_res(user_info, socket_fd);
  if (auth_validate(res, NEED_PASSWORD) < 0) {
    perror("auth.error.invalid_username");
    exit(-1);
  }
  res[0] = 0;

  if (send_req(user_info, pwd_cmd, PWD_CMD_LENGTH, socket_fd) < 0){
    perror('auth.error.bad_request');
    exit(-1);
  }

  res = read_res(user_info, socket_fd);
  if (auth_validate(res, NEED_PASSWORD) < 0) {
    perror('auth.error.invalid_password');
    exit(-1);
  }
  res[0] = 0;

  printf("auth.info.login_success\n");
  return 0;
}