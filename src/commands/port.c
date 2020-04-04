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
    if (is_client_login(client) != LOGGED)
        return (add_message_client(client, E_530PL));
    if (get_size_array(cmd) < 2)
        return (add_message_client(client, E_501));
    //if (client->mode == ACTIVE)
    //    close_fd(&client->data_socket);
    client->mode = ACTIVE;
}