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
#include <netinet/in.h>

/**************************************
 * DEFINE
 *************************************/

#define EXIT_ERROR 84

/**************************************
 * STRUCTURE DEFINITION
 *************************************/

typedef struct server_info_s
{
    struct sockaddr_in address;
    int server_socket;
    int port;
    char *anonymous_home;
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

#endif //NWP_MYFTP_2019_MYFTP_H
