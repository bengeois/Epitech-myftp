/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <commands.h>
#include "myftp.h"

void help(server_info_t *info, client_t *client, char **cmd)
{
    (void)info;
    if (is_client_login(client) != LOGGED)
        return (add_message_client(client, E_530PL));
    if (get_size_array(cmd) == 1) {
        add_message_client(client, E_214C);
        for (int i = 0; commands[i].name != NULL; i++)
            add_message_client(client, "- %s\n", commands[i].name);
        add_message_client(client, E_214);
        return;
    }
    for (int i = 0; commands[i].name != NULL; i++) {
        if (!strcmp(commands[i].name, cmd[1])) {
            add_message_client(client, E_214CD, commands[i].name, commands[i]
            .help);
            return;
        }
    }
    add_message_client(client, E_214CD, cmd[1], "UNKNOWN COMMAND");
}