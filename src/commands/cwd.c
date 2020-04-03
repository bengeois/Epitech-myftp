/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"
#include <sys/stat.h>

static void build_path(char *request, char *actual, char *to_add)
{
    bzero(request, PATH_MAX);
    if (to_add[0] == '/') {
        strcpy(request, to_add);
        return;
    }
    if (actual[strlen(actual) - 1] != '/')
        actual[strlen(actual)] = '/';
    strcpy(request, actual);
    strcat(request, to_add);
}

void cwd(server_info_t *info, client_t *client, char **cmd)
{
    (void)info;
    struct stat info_dir;
    char real_path[PATH_MAX];
    char request_path[PATH_MAX];
    if (is_client_login(client) != LOGGED)
        return (add_message_client(client, E_530PL));
    if (get_size_array(cmd) < 2 || cmd[1] == NULL)
        return (add_message_client(client, E_550F));
    build_path(request_path, client->cur_dir, cmd[1]);
    if (realpath(request_path, real_path) == NULL)
        return (add_message_client(client, E_550F));
    if (stat(real_path, &info_dir) == -1)
        return (add_message_client(client, E_550F));
    if (!S_ISDIR(info_dir.st_mode))
        return (add_message_client(client, E_550F));
    bzero(client->cur_dir, PATH_MAX);
    strcpy(client->cur_dir, real_path);
    add_message_client(client, E_250D);
}