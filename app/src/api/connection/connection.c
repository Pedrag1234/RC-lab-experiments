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

int send_req(user_info * user_info, char * command, size_t size, int socket_fd){

    int bytes = write(socket_fd, command, size);

    if (bytes > 0)
        printf("Number of bytes written %ld\n", bytes);
    else {
        perror("connection.writing_bytes");
        return -1;
    }

    return 0;
}

char * read_res(user_info * user_info, int socket_fd){

    bool reading_finished = false; 
    char temp[1];

    char res[256];
    int size = 1;

    while (!reading_finished)
    {
        if(read(socket_fd, temp, 1) > 0){
            int last_pos = size - 1;

            res[last_pos] = temp;
            size++;

            if (temp == "\n")
                reading_finished = true;
        }
    }

    printf("Response - %s\n",res);

    return 0;
}

int close_connection(int socket_fd){
    if (close(socket_fd) < 0) {
        perror("close()");
        return -1;
    }

    return 0;
}