#include "auth.h"

void auth_request(
  user_info *user_info, 
  const char *cmd, 
  const size_t cmd_len, 
  const res_t req_type, 
  const int socket_fd
){
  char res[BUFFER_SIZE];
  char code[FTP_RES_SIZE];

  if (send_req(cmd, cmd_len, socket_fd) < 0 ){
    perror("auth.error.bad_request");
    exit(-1);
  }
  do
  {
    read_res(socket_fd, res);
  } while (res[3] != ' ');
  
  
  snprintf(code, FTP_RES_SIZE, "%s", res);
  
  if (auth_validate(code, req_type) < 0) {
    printf("code >> %s\n", code);
    printf("req_type >> %d\n", req_type);
    perror("auth.error.no_validate");
    exit(-1);
  }

  memset(res, 0, BUFFER_SIZE);
  memset(code, 0, FTP_RES_SIZE);
}

int auth_validate(char *res, const res_t code)
{
  char code_str[FTP_RES_SIZE];
  my_itoa(code, code_str);

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

  const size_t USR_CMD_LENGTH = strlen(user_info->usr) + 8;
  const size_t PWD_CMD_LENGTH = strlen(user_info->pwd) + 8;

  char welcome_cmd[BUFFER_SIZE] = "telnet ftp.up.pt 21";
  char usr_cmd[USR_CMD_LENGTH];
  char pwd_cmd[PWD_CMD_LENGTH];

  sprintf(usr_cmd, "user %s\r\n", user_info->usr);
  sprintf(pwd_cmd, "pass %s\r\n", user_info->pwd);

  //auth_request(user_info, welcome_cmd, BUFFER_SIZE, WELCOME, socket_fd);
  char res[BUFFER_SIZE];
  char code[FTP_RES_SIZE];

  do
  {
    read_res(socket_fd, res);
  } while (res[3] != ' ');

  snprintf(code, FTP_RES_SIZE, "%s", res);
  
  if (auth_validate(code, WELCOME) < 0) {
    printf("code >> %s\n", code);
    printf("req_type >> %d\n", WELCOME);
    perror("auth.error.no_validate");
    exit(-1);
  }


  auth_request(user_info, usr_cmd, USR_CMD_LENGTH, NEED_PASSWORD, socket_fd);
  auth_request(user_info, pwd_cmd, PWD_CMD_LENGTH, LOGIN_SUCCESS, socket_fd);

  printf("auth.info.login_success\n");

  return 0;
}