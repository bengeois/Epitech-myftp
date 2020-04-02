/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

void quit_client(server_info_t *info)
{
    node_t *temp = info->clients;
    while (temp) {
        if (((client_t*)temp->value)->quit && !tcp_is_waiting_message((
            (client_t*)temp->value)->sending)) {
            disconnect_client(info, &temp, "Client disconnected");
            continue;
        }
        temp = temp->next;
    }
}