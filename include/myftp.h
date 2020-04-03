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
#include <pwd.h>
#include "my_network.h"
#include "generic_list.h"
#include "error_code.h"

/**************************************
 * DEFINE
 *************************************/

#define EXIT_ERROR 84
#define LOOP_CONTINUE -1

#define LISTEN_CLIENT_QUEUE 10
#define SERVER_IP "127.0.0.1"

bool server_stop;

/**************************************
 * ENUM DEFINITION
 *************************************/

typedef enum transfer_mode_s
{
    PASSIVE,
    ACTIVE,
    UNKNOWN
} transfer_mode_t;

/**************************************
 * STRUCTURE DEFINITION
 *************************************/

typedef struct client_s
{
    int socket;
    struct sockaddr_in addr;
    transfer_mode_t mode;
    message_t *received;
    message_t *sending;
    char *username;
    char *passwd;
    char *home_dir;
    bool quit;
} client_t;

typedef struct server_info_s
{
    struct sockaddr_in address;
    int server_socket;
    int port;
    char *anonymous_home;
    list_t clients;
    fd_set read_fd;
    fd_set write_fd;
    fd_set except_fd;
    struct timeval timeout;
} server_info_t;

typedef struct commands_s
{
    char *name;
    void (*func)(server_info_t*, client_t*, char**);
    char *help;
} command_t;

/**************************************
 * FUNCTION PREDECLARATION
 *************************************/

/* UTILS */
char **my_strtok(char *str, char sep);
int get_size_array(char **array);
char **free_array(char **array);

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


/* CLIENT */
client_t *new_client(void);
void delete_client(void *data);
void delete_sending(void *data);
void disconnect_client(server_info_t *info, node_t **temp, char *message);
int get_new_client_info(server_info_t *info, client_t *new_client);
int is_new_client(server_info_t *info);
void add_message_client(client_t *client, char *str, ...);


/* SERVER */
int start_server(server_info_t *info);
void stop_server(int signal);
int running_server(server_info_t *info);
void manage_timeout_select(struct timeval *timeout);
int handle_socket_activities(server_info_t *info);
void quit_client(server_info_t *info);
int handle_client_activities(server_info_t *info);
int detect_command(server_info_t *info, node_t *temp, char *str);


/* COMMAND */
void quit(server_info_t *info, client_t *client, char **cmd);
void user(server_info_t *info, client_t *client, char **cmd);
void pass(server_info_t *info, client_t *client, char **cmd);

#endif //NWP_MYFTP_2019_MYFTP_H
