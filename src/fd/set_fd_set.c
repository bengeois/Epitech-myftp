/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

void set_fd_set(server_info_t *info)
{
    info->sock_max = info->server_socket;
    FD_ZERO(&info->read_fd);
    FD_ZERO(&info->write_fd);
    FD_ZERO(&info->except_fd);
    //FD_SET(STDIN_FILENO, &info->read_fd); // A VOIR UTILITE
    FD_SET(info->server_socket, &info->read_fd);
    //FD_SET(STDIN_FILENO, &info->except_fd); // A VOIR UTILITE
    FD_SET(info->server_socket, &info->except_fd);
    for (node_t *temp = info->connections; temp; temp = temp->next) {
        if (((connection_t*)temp->value)->socket == -1)
            continue;
        if (((connection_t*)temp->value)->socket > info->sock_max)
            info->sock_max = ((connection_t*)temp->value)->socket;
        //if (1)// A Voir la condition pour write)
        //    FD_SET(((connection_t*)temp->value)->socket, &info->write_fd);
        FD_SET(((connection_t*)temp->value)->socket, &info->read_fd);
        FD_SET(((connection_t*)temp->value)->socket, &info->except_fd);
    }
}