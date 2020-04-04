/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

void port(server_info_t *info, client_t *client, char **cmd)
{
    (void)info;
    (void)cmd;
    add_message_client(client, E_221);
    client->quit = true;
}