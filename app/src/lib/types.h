#pragma once

typedef struct user_info user_info;

struct user_info
{
    char usr[128];
    char pwd[128];
    char host[256];
    char path[240];
    char ip[128];
    char f_name[128];
    char hostname[128];
};
