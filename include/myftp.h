/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#ifndef NWP_MYFTP_2019_MYFTP_H
#define NWP_MYFTP_2019_MYFTP_H

/**************************************
 * INCLUDE
 *************************************/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netinet/in.h>
#include "my_network.h"
#include "generic_list.h"

/**************************************
 * DEFINE
 *************************************/

#define EXIT_ERROR 84
#define LISTEN_CLIENT_QUEUE 10
#define SERVER_IP "127.0.0.1"

/**************************************
 * STRUCTURE DEFINITION
 *************************************/

typedef struct connection_s
{
    int socket;
    struct sockaddr_in addr;
} connection_t;

typedef struct server_info_s
{
    struct sockaddr_in address;
    int server_socket;
    int port;
    char *anonymous_home;
    list_t connections;
    fd_set read_fd;
    fd_set write_fd;
    fd_set except_fd;
    int sock_max;
    struct timeval timeout;
} server_info_t;

/**************************************
 * FUNCTION PREDECLARATION
 *************************************/

/* MAIN FUNCTION */
int myftp(int argc, char **argv);
int get_user_info(int argc, char **argv, server_info_t *info);


/* INIT FUNCTION */
server_info_t *init_server_info(void);


/* ERROR FUNCTION */
int exit_properly(server_info_t *info, int error_code);


/* FD */
void close_fd(int *fd);
void set_fd_set(server_info_t *info);
int socket_error(server_info_t *info);


/* CONNECTION */
connection_t *new_connection(void);
void delete_connection(void *data);

/* SERVER */
int start_server(server_info_t *info);
int running_server(server_info_t *info);
int get_new_client_info(server_info_t *info, connection_t *new_client);
int is_new_client(server_info_t *info);
void manage_timeout_select(server_info_t *info);

#endif //NWP_MYFTP_2019_MYFTP_H
