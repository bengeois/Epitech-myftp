/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"
#include "commands.h"

int detect_command(server_info_t *info, node_t *temp)
{
    char **cmd_tab = NULL;
    if (((client_t*)temp->value)->received == NULL)
        return (TCP_OK);
    cmd_tab = my_strtok(((client_t*)temp->value)->received, ' ');
    if (cmd_tab == NULL)
        return (TCP_OK);
    for (int i = 0; commands[i].name != NULL; i++) {
        if (!strcasecmp(commands[i].name, cmd_tab[0])) {
            commands[i].func(info, temp->value, cmd_tab);
            free(cmd_tab);
            free(((client_t*)temp->value)->received);
            ((client_t*)temp->value)->received = NULL;
            return (TCP_OK);
        }
    }
    add_message_client(temp->value, E_500);
    free(cmd_tab);
    free(((client_t*)temp->value)->received);
    ((client_t*)temp->value)->received = NULL;
    return (TCP_OK);
}

int handle_client_activities(server_info_t *info)
{
    node_t *temp = info->clients;
    while (temp) {
        if (detect_command(info, temp) == TCP_ERROR)
            return (TCP_ERROR);
        temp = temp->next;
    }
    return (TCP_OK);
}