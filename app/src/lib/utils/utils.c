#include "utils.h"

int argsParser(char * params, user_info * user_info){
    return -1;
}

int getIp(user_info * user_info){
    struct hostent *h;
    
    if ((h = gethostbyname(user_info->hostname)) == NULL)
    {
        herror("gethostbyname()");
        return -1;
    }
    
    strcpy(user_info, inet_ntoa(*((struct in_addr *) h->h_addr)));
    return 0;
}

int getFileName(user_info * user_info){
    return -1;
}