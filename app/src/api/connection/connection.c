#include "connection.h"


int init_connection(user_info * user_info){
    struct sockaddr_in server_addr;
    int socket_fd;

     /*server address handling*/
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(user_info->ip);    /*32 bit Internet address network byte ordered*/
    server_addr.sin_port = htons(user_info->port);        /*server TCP port must be network byte ordered */

    /*open a TCP socket*/
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        return -1;
    }
    /*connect to the server*/
    if (connect(socket_fd,
                (struct sockaddr *) &server_addr,
                sizeof(server_addr)) < 0) {
        perror("connect()");
        return -1;
    }

    return socket_fd;
}

int send_req(user_info * user_info, char * command, int size, int socket_fd){

    int bytes = write(socket_fd, command, size);

    if (bytes > 0)
        printf("Number of bytes written %ld\n", bytes);
    else {
        perror("write()");
        return -1;
    }

    return 0;
}

int read_rep(user_info * user_info, int socket_fd, char * reply){

    bool reading_finished = false; 
    
    while (reading_finished)
    {
        /* code */
    }
    

    return -1;
}

int close_connection(){
    if (close(socket_fd)<0) {
        perror("close()");
        return -1;
    }

    return 0;
}