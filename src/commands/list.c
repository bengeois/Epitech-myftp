/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

static void get_complete_list_cmd(char *complete_cmd, char **cmd)
{
    bzero(complete_cmd, PATH_MAX);
    strcpy(complete_cmd, "ls -l ");
    if (get_size_array(cmd) > 1 && access(cmd[1], F_OK) == 0)
        strcat(complete_cmd, cmd[1]);
}

static void exec_cmd_list(client_t *client, char **cmd)
{
    FILE *output_cmd = NULL;
    char str[4096];
    char complete_cmd[PATH_MAX];

    if (chdir(client->cur_dir) == -1) {
        dprintf(client->socket_data, "Failed to exec LIST command");
        exit(0);
    }
    bzero(str, 4096);
    get_complete_list_cmd(complete_cmd, cmd);
    output_cmd = popen(complete_cmd, "r");
    while (fread(str, 1, 256, output_cmd)) {
        dprintf(client->socket_data, "%s", str);
        bzero(str, 4096);
    }
    fclose(output_cmd);
    exit(0);
}

void list(server_info_t *info, client_t *client, char **cmd)
{
    (void)info;
    pid_t process = -1;
    if (is_client_login(client) != LOGGED)
        return (add_message_client(client, E_530PL));
    if (client->mode == UNDEFINED_MODE)
        return (add_message_client(client, E_425));
    if (handle_mode_open(client) == TCP_ERROR)
        return (add_message_client(client, E_425U));
    if ((process = fork()) == -1) {
        close_fd(&client->socket_mode);
        return (add_message_client(client, E_425U));
    }
    if (process == 0)
        exec_cmd_list(client, cmd);
    else
        add_process_to_client(client, process);
    return (add_message_client(client, E_150));
}