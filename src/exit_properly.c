/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <zconf.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include "myftp.h"

int exit_properly(server_info_t *info, int error_code)
{
    fprintf(stdout, "Server is shutting down\n");
    if (!info)
        return (error_code);
    if (fcntl(info->server_socket, F_GETFD) != -1 || errno != EBADF)
        close(info->server_socket);
    free(info);
    fprintf(stdout, "Server shut down\n");
    return (error_code);
}