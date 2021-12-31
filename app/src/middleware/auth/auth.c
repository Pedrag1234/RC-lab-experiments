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

  char usr_cmd[BUFFER_SIZE];
  char pwd_cmd[BUFFER_SIZE];

  sprintf(usr_cmd, "USER %s\r\n", user_info->usr);
  sprintf(pwd_cmd, "PASS %s\r\n", user_info->pwd);

  char res[BUFFER_SIZE];
  char code[FTP_RES_SIZE];

  do
  {
    read_res(socket_fd, res);
  } while (res[3] != ' ');

  snprintf(code, FTP_RES_SIZE, "%s", res);
  
  if (auth_validate(code, WELCOME) < 0) {
    perror("auth.error.no_validate");
    exit(-1);
  }

  memset(res, 0, BUFFER_SIZE);
  memset(code, 0, FTP_RES_SIZE);

  auth_request(user_info, usr_cmd, strlen(usr_cmd), NEED_PASSWORD, socket_fd);
  auth_request(user_info, pwd_cmd, strlen(pwd_cmd), LOGIN_SUCCESS, socket_fd);

  printf("auth.info.login_success\n");

  return 0;
}

void auth_passive(
  user_info *user_info, 
  const char *cmd, 
  const size_t cmd_len, 
  const res_t req_type, 
  const int socket_fd,
  char *ip,
  int *port
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
    perror("auth.error.no_validate");
    exit(-1);
  }

  strtok(res,"(");
  char* i1 = strtok(NULL,",");
  char* i2 = strtok(NULL,",");
  char* i3 = strtok(NULL,",");
  char* i4 = strtok(NULL,",");

  sprintf(*ip,"%s.%s.%s.%s", i1,i2,i3,i4);

  int port1 = atoi(strtok(NULL,","));
  int port2 = atoi(strtok(NULL,","));

  *port = port1 * 256 + port2;

  memset(res, 0, BUFFER_SIZE);
  memset(code, 0, FTP_RES_SIZE);
}