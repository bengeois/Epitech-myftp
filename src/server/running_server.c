/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

int running_server(server_info_t *info)
{
    struct timeval timeout;
    while (!server_stop) {
        set_fd_set(info);
        manage_timeout_select(&timeout);
        if (select(FD_SETSIZE, &info->read_fd, &info->write_fd,
        &info->except_fd, &timeout) == -1) {
            perror("[SERVER]");
            return (EXIT_FAILURE);
        }
        if (socket_error(info) == TCP_ERROR)
            return (EXIT_FAILURE);
        if (is_new_client(info) == TCP_ERROR)
            return (EXIT_FAILURE);
        if (handle_socket_activities(info) == TCP_ERROR)
            return (EXIT_FAILURE);
        if (handle_client_activities(info) == TCP_ERROR)
            return (EXIT_FAILURE);
        quit_client(info);
    }
    return (EXIT_SUCCESS);
}