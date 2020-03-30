/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#ifndef NWP_MYFTP_2019_MYFTP_H
#define NWP_MYFTP_2019_MYFTP_H

#include <stdlib.h>

#define EXIT_ERROR 84

typedef struct server_info_s
{
    int port;
    char *anonymous_home;
} server_info_t;

/* MAIN FUNCTION */
int myftp(int argc, char **argv);
int get_user_info(int argc, char **argv, server_info_t *info);

/* INIT FUNCTION */
server_info_t *init_server_info(void);

#endif //NWP_MYFTP_2019_MYFTP_H
