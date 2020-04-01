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
    info->clients = NULL;
    FD_ZERO(&info->read_fd);
    FD_ZERO(&info->write_fd);
    FD_ZERO(&info->except_fd);
    bzero(&info->timeout, sizeof(struct timeval));
    info->timeout.tv_sec = 2; // A FAIRE
    return (info);
}