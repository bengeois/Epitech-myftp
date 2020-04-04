/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

static void exec_cmd_list(client_t *client)
{
    FILE *output_cmd = NULL;
    char str[4096];

    if (chdir(client->cur_dir) == -1) {
        dprintf(client->data_client, "Failed to exec LIST command");
        exit(0);
    }
    bzero(str, 4096);
    output_cmd = popen("ls -l", "r");
    while (fread(str, 1, 256, output_cmd)) {
        dprintf(client->data_client, "%s", str);
        bzero(str, 4096);
    }
    fclose(output_cmd);
    exit(0);
}

void list(server_info_t *info, client_t *client, char **cmd)
{
    (void)info;
    (void)cmd;
    pid_t process = -1;
    if (is_client_login(client) != LOGGED)
        return (add_message_client(client, E_530PL));
    if (client->mode == UNDEFINED_MODE)
        return (add_message_client(client, E_425));
    if (handle_mode_open(client) == TCP_ERROR)
        return (add_message_client(client, E_425U));
    if ((process = fork()) == -1) {
        close_fd(&client->data_socket);
        return (add_message_client(client, E_425U));
    }
    if (process == 0)
        exec_cmd_list(client);
    else
        add_process_to_client(client, process);
    return (add_message_client(client, E_150));
}