/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

int socket_error(server_info_t *info)
{
    if (FD_ISSET(info->server_socket, &info->except_fd)) {
        fprintf(stderr, "[SERVER] Error with the socket server.\n");
        return (EXIT_FAILURE);
    }
    if (FD_ISSET(STDIN_FILENO, &info->except_fd)) {
        fprintf(stderr, "[SERVER] Error with the server.\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}