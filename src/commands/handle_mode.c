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
        client->data_client = accept(client->data_socket, (struct sockaddr *)
        &client->data_addr, (socklen_t *) &data_addr_len);
        if (client->data_client < 0)
            return (TCP_ERROR);
        return (TCP_OK);
    }
    return (TCP_OK);
}