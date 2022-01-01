#pragma once

#include "macros.h"

typedef struct user_info user_info;
typedef struct client_info client_info;

typedef enum res_t res_t;
typedef enum ftp_mode_t ftp_mode_t;

enum ftp_mode_t {
    ACTIVE,
    PASV
};

enum res_t {
    CONFIRM = 200,
    NEED_PASSWORD = 331,
    LOGIN_SUCCESS = 230,
    PASSIVE_MODE = 227,
    WELCOME = 220,
    NOOP = 404
};

struct client_info {
    int ip1;
    int ip2;
    int ip3;
    int ip4;
    int port1;
    int port2;
};

struct user_info
{
    char usr[BUFFER_SIZE];
    char pwd[BUFFER_SIZE];
    char host[BUFFER_SIZE];
    int port;
    char path[BUFFER_SIZE];
    char ip[BUFFER_SIZE];
    char f_name[BUFFER_SIZE];
    char hostname[BUFFER_SIZE];
};
