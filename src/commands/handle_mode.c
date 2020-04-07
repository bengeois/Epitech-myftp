/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

int handle_mode_open(client_t *client)
{
    int data_addr_len = sizeof(client->data_addr);
    if (client->mode == PASSIVE) {
        client->socket_data = accept(client->socket_mode, (struct sockaddr *)
        &client->data_addr, (socklen_t *) &data_addr_len);
        if (client->socket_data < 0)
            return (TCP_ERROR);
        return (TCP_OK);
    } else if (client->mode == ACTIVE) {
        if (connect(client->socket_data, (struct sockaddr *) &client->data_addr,
            data_addr_len) < 0)
            return (TCP_ERROR);
        return (TCP_OK);
    }
    return (TCP_OK);
}