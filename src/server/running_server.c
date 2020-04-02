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
    while (true) {
        set_fd_set(info);
        manage_timeout_select(&timeout);
        if (select(FD_SETSIZE, &info->read_fd, &info->write_fd,
        &info->except_fd, &timeout) == -1) {
            perror("[SERVER]");
            return (EXIT_FAILURE);
        }
        if (socket_error(info) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        if (is_new_client(info) == EXIT_FAILURE)
            return (EXIT_FAILURE);
        if (handle_socket_activities(info) == EXIT_FAILURE)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}