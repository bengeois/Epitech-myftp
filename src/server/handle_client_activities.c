/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"
#include "commands.h"

int detect_command(server_info_t *info, node_t *temp, char *str)
{
    char **cmd_tab = NULL;
    cmd_tab = my_strtok(str, ' ');
    if (cmd_tab == NULL)
        return (TCP_OK);
    for (int i = 0; commands[i].name != NULL; i++) {
        if (!strcasecmp(commands[i].name, cmd_tab[0])) {
            commands[i].func(info, temp->value, cmd_tab);
            free_array(cmd_tab);
            return (TCP_OK);
        }
    }
    if (is_client_login(temp->value) != LOGGED)
        add_message_client(temp->value, E_530PL);
    else
        add_message_client(temp->value, E_500);
    free_array(cmd_tab);
    return (TCP_OK);
}

int handle_client_activities(server_info_t *info)
{
    node_t *temp = info->clients;
    char *line = NULL;

    while (temp) {
        if ((line = tcp_getline_receive(((client_t*)temp->value)->received))
        == NULL) {
            temp = temp->next;
            continue;
        }
        if (detect_command(info, temp, line) == TCP_ERROR) {
            free(line);
            return (TCP_ERROR);
        }
        free(line);
        temp = temp->next;
    }
    return (TCP_OK);
}