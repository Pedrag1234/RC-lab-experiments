#pragma once

#define BUFFER_SIZE 256
#define BUFFER_SIZE_LG 2048
#define FILE_BUFFER_SIZE 30000

#define FTP_RES_SIZE 4
#define FTP_TYPE "ftp:"

#define DEFAULT_USR "anonymous"
#define DEFAULT_PWD "anonymous--pwd"

#define FTP_SERVER_PORT 21 
#define FTP_DATA_PORT 20

#define PASV_CMD "PASV\r\n"
#define TYPE_CMD "TYPE L 8\r\n"
#define RETR_CMD "RETR"