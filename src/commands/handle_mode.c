/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

static int timeout_passive_mode(client_t *client)
{
    struct timeval timeout = {8, 0};
    fd_set read_fd;

    FD_ZERO(&read_fd);
    FD_SET(client->socket_mode, &read_fd);
    if (select(FD_SETSIZE, &read_fd, NULL, NULL, &timeout) == -1)
        return (TCP_ERROR);
    if (!FD_ISSET(client->socket_mode, &read_fd)) {
        client->mode = UNDEFINED_MODE;
        add_message_client(client, E_421);
        return (TCP_ERROR);
    }
    return (TCP_OK);
}

int handle_mode_open(client_t *client)
{
    int data_addr_len = sizeof(client->data_addr);
    if (client->mode == PASSIVE) {
        if (timeout_passive_mode(client) == TCP_ERROR)
            return (TCP_ERROR);
        client->socket_data = accept(client->socket_mode, (struct sockaddr *)
        &client->data_addr, (socklen_t *) &data_addr_len);
        if (client->socket_data < 0) {
            add_message_client(client, E_425U);
            return (TCP_ERROR);
        }
        return (TCP_OK);
    } else if (client->mode == ACTIVE) {
        if (connect(client->socket_data, (struct sockaddr *) &client->data_addr,
        data_addr_len) < 0) {
            add_message_client(client, E_425U);
            return (TCP_ERROR);
        }
        return (TCP_OK);
    }
    return (TCP_OK);
}