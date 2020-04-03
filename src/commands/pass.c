/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

static int connect_other_user(server_info_t *info, client_t *client, char **cmd)
{
    struct passwd *user_info;
    if (cmd[1] == NULL)
        return (0);
    if ((user_info = getpwnam(client->username)) == NULL)
        return (0);
    if (strcmp(user_info->pw_passwd, cmd[1]) != 0)
        return (0);
    client->passwd = strdup(user_info->pw_passwd);
    client->home_dir = strdup(user_info->pw_dir);
    (void)info;
    return (1);
}

static int connect_anonymous_user(server_info_t *info, client_t *client, char
**cmd)
{
    if (strcmp(client->username, "Anonymous") != 0)
        return (0);
    if (cmd[1] != NULL)
        return (0);
    client->passwd = strdup("OK");
    client->home_dir = strdup(info->anonymous_home);
    return (1);
}

void pass(server_info_t *info, client_t *client, char **cmd)
{
    if (client->username == NULL)
        return (add_message_client(client, E_503));
    if (client->username != NULL && client->passwd != NULL)
        return (add_message_client(client, E_230A));
    if (connect_anonymous_user(info, client, cmd))
        return (add_message_client(client, E_230));
    if (connect_other_user(info, client, cmd))
        return (add_message_client(client, E_230));
    free(client->username);
    client->username = NULL;
    return (add_message_client(client, E_530L));
}
