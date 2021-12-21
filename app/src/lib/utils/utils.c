#include "utils.h"

int argsParser(char * params, user_info * user_info){

    char* type = strtok(params, "/");
    char* user_url = strtok(NULL, "/");
    char* path = strtok(NULL, "");

    if(strcmp(type,FTP_TYPE) != 0){
        printf("Not FTP aborting ...");
        return -1;
    }
        

    char* usr_pwd = strtok(user_url, "@");
    char* url = strtok(NULL, "");

    if (url != NULL)
    {
        //User provided
         char* usr = strtok(usr_pwd, ":");
         char* pwd = strtok(NULL, "");
        
        if (pwd != NULL)
        {
            strcpy(user_info->usr,usr);
            strcpy(user_info->pwd,pwd);
            strcpy(user_info->hostname,url);
        }
        else
        {
            strcpy(user_info->usr,DEFAULT_USR);
            strcpy(user_info->pwd,DEFAULT_PWD);
            strcpy(user_info->hostname,url);
        }
    }
    else
    {   
        //User not provided
        strcpy(user_info->usr,DEFAULT_USR);
        strcpy(user_info->pwd,DEFAULT_PWD);
        strcpy(user_info->hostname,usr_pwd);
    }

    if (path != NULL)
    {
        strcpy(user_info->path,path);
    }
    else
    {
        printf("No path specified");
        return -1;
    }
    
    user_info->port = DEFAULT_PORT;

    getFileName(user_info);
    getIp(user_info);

    return 0;
}

void printUserInfo(user_info * user_info){

    printf("*********************************************************************************\n");
    printf("INFO:\n");
    printf("Username : %s \t Password : %s\n", user_info->usr,user_info->pwd);
    printf("Host Name : %s \t Path : %s\n", user_info->hostname,user_info->path);
    printf("Host : %s \t IP : %s \t Port : %d \n",user_info->host,user_info->ip,user_info->port);
    printf("File Name : %s\n",user_info->f_name);
    printf("*********************************************************************************\n");
}

int getIp(user_info * user_info){
    struct hostent *h;
    
    if ((h = gethostbyname(user_info->hostname)) == NULL)
    {
        herror("gethostbyname()");
        return -1;
    }
    strcpy(user_info->host,(char*)h->h_name);
    strcpy(user_info->ip, inet_ntoa( *( (struct in_addr *)h->h_addr_list[0] ) ));
    return 0;
}

int getFileName(user_info * user_info){
    char temp[256];
    strcpy(temp,user_info->path);

    char filename[256];
    char * token = strtok(temp,"/");
    while (token != NULL)
    {
        strcpy(filename,token);
        token = strtok(NULL,"/");
    }
    
    strcpy(user_info->f_name,filename);

    return -1;
}