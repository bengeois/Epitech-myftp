/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <stdio.h>
#include <string.h>
#include "myftp.h"

server_info_t *init_server_info(void)
{
    server_info_t *info = malloc(sizeof(server_info_t));

    if (!info) {
        fprintf(stderr, "malloc() failed\n");
        return (NULL);
    }
    bzero(&info->address, sizeof(struct sockaddr_in));
    info->server_socket = -1;
    info->port = -1;
    info->anonymous_home = NULL;
    info->connections = NULL;
    return (info);
}