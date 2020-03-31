/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <arpa/inet.h>
#include "myftp.h"

void client_error(server_info_t *info, node_t **temp)
{
    node_t *to_delete = *temp;
    *temp = (*temp)->next;
    fprintf(stderr, "Client exception : %s:%i closed\n",
    inet_ntoa(((connection_t*)to_delete->value)->addr.sin_addr),
    ntohs(((connection_t*)to_delete->value)->addr.sin_port));
    close(((connection_t*)to_delete->value)->socket);
    list_del_elem_at_value(&info->connections, to_delete->value,
    delete_connection);
}

int handle_socket_activities(server_info_t *info)
{
    node_t *temp = info->connections;
    while (temp) {
        if (FD_ISSET(((connection_t*)temp->value)->socket, &info->except_fd)) {
            client_error(info, &temp);
            continue;
        }
        temp = temp->next;
    }
    return (EXIT_SUCCESS);
}