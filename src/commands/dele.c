/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

void dele(server_info_t *info, client_t *client, char **cmd)
{
    (void)info;
    if (is_client_login(client) != LOGGED)
        return (add_message_client(client, E_530PL));
    if (get_size_array(cmd) < 2)
        return (add_message_client(client, E_530P));
    if (remove(cmd[1]))
        return (add_message_client(client, E_550));
    add_message_client(client, E_250);
}