/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <arpa/inet.h>
#include "myftp.h"

void disconnect_client(server_info_t *info, node_t **temp, char *message)
{
    node_t *to_delete = *temp;
    *temp = (*temp)->next;
    fprintf(stderr, "%s : %s:%i closed\n", message,
    inet_ntoa(((client_t*)to_delete->value)->addr.sin_addr),
    ntohs(((client_t*)to_delete->value)->addr.sin_port));
    close(((client_t*)to_delete->value)->socket);
    list_del_elem_at_value(&info->clients, to_delete->value,
    delete_client);
}