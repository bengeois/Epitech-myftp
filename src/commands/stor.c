/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <fcntl.h>
#include "myftp.h"

static void exec_cmd_stor(client_t *client, char **cmd)
{
    int output_file = open(cmd[1], O_CREAT | O_WRONLY, 0664);
    char str[4096 + 1];

    if (chdir(client->cur_dir) == -1 || output_file == -1) {
        dprintf(client->socket_data, "Failed to exec STOR command");
        exit(0);
    }
    bzero(str, 4096 + 1);

    while (read(client->socket_data, str, 4096) != 0) {
        dprintf(output_file, "%s", str);
        bzero(str, 4096 + 1);
    }
    close(output_file);
    exit(0);
}

static bool is_file_on_client(char *file)
{
    int fd = open(file, O_CREAT | O_WRONLY, 0664);
    if (fd == -1)
        return (false);
    close(fd);
    return (true);
}

void stor(server_info_t *info, client_t *client, char **cmd)
{
    (void)info;
    pid_t process;
    if (is_client_login(client) != LOGGED)
        return (add_message_client(client, E_530PL));
    if (client->mode == UNDEFINED_MODE)
        return (add_message_client(client, E_425));
    if (get_size_array(cmd) < 2)
        return (add_message_client(client, E_501));
    if (!is_file_on_client(cmd[1]))
        return (add_message_client(client, E_550));
    if (handle_mode_open(client) == TCP_ERROR)
        return (add_message_client(client, E_425U));
    if ((process = fork()) == -1) {
        close_fd(&client->socket_mode);
        return (add_message_client(client, E_425U));
    }
    if (process == 0)
        exec_cmd_stor(client, cmd);
    else
        add_process_to_client(client, process);
    return (add_message_client(client, E_150));

}