/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

void set_fd_set(server_info_t *info)
{
    FD_ZERO(&info->read_fd);
    FD_ZERO(&info->write_fd);
    FD_ZERO(&info->except_fd);
    FD_SET(info->server_socket, &info->read_fd);
    FD_SET(info->server_socket, &info->except_fd);
    for (node_t *temp = info->clients; temp; temp = temp->next) {
        if (((client_t*)temp->value)->socket == -1)
            continue;
        if (tcp_is_waiting_message(((client_t*)temp->value)->sending))
            FD_SET(((client_t*)temp->value)->socket, &info->write_fd);
        FD_SET(((client_t*)temp->value)->socket, &info->read_fd);
        FD_SET(((client_t*)temp->value)->socket, &info->except_fd);
    }
}