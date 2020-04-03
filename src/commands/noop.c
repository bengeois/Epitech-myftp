/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

void noop(server_info_t *info, client_t *client, char **cmd)
{
    (void)info;
    (void)cmd;
    if (is_client_login(client) != LOGGED)
        return (add_message_client(client, E_530PL));
}