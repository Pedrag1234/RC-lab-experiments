#pragma once

typedef struct user_info user_info;

struct user_info
{
    char usr[256];
    char pwd[256];
    char host[256];
    char port[256];
    char path[256];
    char ip[256];
    char f_name[256];
    char hostname[256];
};
