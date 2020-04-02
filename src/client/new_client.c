/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

client_t *new_client(void)
{
    client_t *new_client = malloc(sizeof(client_t));

    if (!new_client)
        return (NULL);
    new_client->socket = -1;
    new_client->received = NULL;
    new_client->sending = tcp_new_message();
    if (new_client->sending == NULL) {
        free(new_client);
        return (NULL);
    }
    new_client->quit = false;
    return (new_client);
}