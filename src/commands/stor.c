/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <sys/stat.h>
#include <fcntl.h>
#include "myftp.h"

static void exec_cmd_stor(client_t *client, char **cmd)
{
    int output_file = -1;
    char str[4096 + 1];

    if (chdir(client->cur_dir) == -1) {
        dprintf(client->socket_data, "Failed to exec STOR command");
        exit(0);
    } else if ((output_file = open(cmd[1], O_CREAT | O_WRONLY, 0664)) == -1) {
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

static bool can_create_file_on_server(client_t *client, char *file)
{
    char real_path[PATH_MAX];
    bzero(real_path, PATH_MAX);
    int fd = -1;
    if (file[0] != '/') {
        strcpy(real_path, client->cur_dir);
        if (real_path[strlen(real_path) - 1] != '/')
            real_path[strlen(real_path)] = '/';
        strcat(real_path, file);
    } else {
        strcpy(real_path, file);
    }
    if ((fd = open(real_path, O_CREAT | O_WRONLY, 0664)) == -1)
        return (false);
    close(fd);
    struct stat info;
    if (stat(real_path, &info) == -1)
        return (false);
    if (S_ISDIR(info.st_mode))
        return (false);
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
    if (!can_create_file_on_server(client, cmd[1]))
        return (add_message_client(client, E_550));
    if (handle_mode_open(client) == TCP_ERROR)
        return;
    if ((process = fork()) == -1) {
        close_fd(&client->socket_mode);
        return (add_message_client(client, E_425U));
    }
    (process == 0) ? exec_cmd_stor(client, cmd) :
    add_process_to_client(client, process);
    return (add_message_client(client, E_150));

}