/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

void user(server_info_t *info, client_t *client, char **cmd)
{
    if (cmd[1] == NULL)
        return (add_message_client(client, E_530P));
    if (client->username != NULL)
        return (add_message_client(client, E_530C));
    client->username = strdup(cmd[1]);
    return (add_message_client(client, E_331));
    (void)info;
}