/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

connection_t *new_connection(void)
{
    connection_t *new_client = malloc(sizeof(connection_t));

    if (!new_client)
        return (NULL);
    new_client->socket = -1;
    new_client->received = NULL;
    new_client->sending = NULL;
    return (new_client);
}