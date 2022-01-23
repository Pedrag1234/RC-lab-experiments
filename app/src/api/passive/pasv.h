#pragma once

#include "../../middleware/auth/auth.h";
#include "../../middleware/connection/connection.h";

/**
 * @brief parse the response from entering passive mode and save the info
 * 
 * @param client_info struct where the ip and port are saved
 * @param res response from the server
 * 
 * @return int 0 if success
 */
int pasv_get_client_info(client_info *client_info, const char *res);

/**
 * @brief build ip from where we will download the file 
 * 
 * @param client_ip ip built
 * @param client_info struct used to build the ip
 * 
 * @return int 0 if success
 */
int pasv_get_client_ip(char *client_ip, const client_info *client_info);


/**
 * @brief build the port where we will download the file from
 * 
 * @param client_info struct used to build the port
 * 
 * @return int 0 if success
 */
int pasv_get_client_port(const client_info * client_info);


/**
 * @brief logins user and sets the connection to passive mode
 * 
 * @param user_info contains the info to connect to the server
 * @param server_fd socket file descriptor to the server
 * @param client_ip ip used for downloading the file
 * 
 * @return int port for downloading the file
 */
int pasv_connect(user_info *user_info, int server_fd, char *client_ip);

/**
 * @brief Sends retrieve command to download the file
 * 
 * @param socket_fd socket file descriptor to send command
 * @param user_info not used
 * @return int 0 if success
 */
int pasv_retr(const int socket_fd, const user_info *user_info);

/**
 * @brief Downloads the file requested
 * 
 * @param user_info contains info about the ip and port to connect to server and download
 * @return int 0 if success
 */
int pasv_download(user_info *user_info);
