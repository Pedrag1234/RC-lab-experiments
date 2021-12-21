#pragma once

#include "macros.h"

typedef struct user_info user_info;
typedef enum res_t res_t;

enum res_t {
    CONFIRM = 2,
    NEED_PASSWORD = 331,
    LOGIN_SUCCESS = 230,
    PASSIVE_MODE = 227,

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
