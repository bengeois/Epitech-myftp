/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

int is_client_login(client_t *client)
{
    if (client->username == NULL || client->passwd == NULL)
        return (UNLOGGED);
    return (LOGGED);
}