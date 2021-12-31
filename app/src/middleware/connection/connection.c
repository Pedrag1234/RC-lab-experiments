#include "connection.h"

int init_connection(user_info * user_info)
{
    struct sockaddr_in server_addr;
    int socket_fd;

     /*server address handling*/
    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(user_info->ip);    /*32 bit Internet address network byte ordered*/
    server_addr.sin_port = htons(user_info->port);             /*server TCP port must be network byte ordered */

    /*open a TCP socket*/
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("connection.error.socket_open");
        exit(-1);
    }

    /*connect to the server*/
    if (connect(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("connection.error.server_connect");
        exit(-1);
    }

    printf("\nconnection.info.open.success: {socket_fd: %d}\n", socket_fd);
    return socket_fd;
}

int send_req(
    const char *cmd, 
    const size_t cmd_len, 
    const int socket_fd
){
    int bytes = write(socket_fd, cmd, cmd_len);

    if (bytes < 0) {
        perror("connection.error.send_request");
        return -1;
    }

    printf("\nconnection.info.request_sent: {socket_fd: %d, cmd: %s}\n", socket_fd, cmd);

    sleep(1); 

    return 0;
}

int read_res(int socket_fd, char *res)
{
    char buf[1]; 
    int i = 0;
    
    size_t bytes = read(socket_fd, buf, 1);

    if(bytes < 0) {
        perror("connection.error.read_response");
        return -1;
    }

    res[i++] = buf[0];

    while(buf[0] != '\n') {
        bytes = read(socket_fd, buf, 1);
        
        if(bytes < 0){
            perror("connection.error.read_response");
            return -1;
        }
        
        if(bytes == 0) 
            break;

        res[i++] = buf[0];
    }
    res[i] = '\0';

    printf("\nconnection.info.response_read: {socket_fd: %d, res: %s}\n", socket_fd, res);

    return 0;
}

int close_connection(int socket_fd)
{
    if (close(socket_fd) < 0) {
        perror("connection.error.close_connection");
        return -1;
    }

    printf("\nconnection.info.close.success: {socket_fd: %d}\n", socket_fd);
    return 0;
}