/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

client_t *new_client(void)
{
    client_t *new_client = malloc(sizeof(client_t));
    if (!new_client) return (NULL);
    new_client->socket = -1;
    new_client->received = NULL;
    new_client->mode = UNDEFINED_MODE;
    new_client->username = NULL;
    new_client->passwd = NULL;
    bzero(&new_client->home_dir, PATH_MAX * sizeof(char));
    bzero(&new_client->cur_dir, PATH_MAX * sizeof(char));
    new_client->socket_mode = -1;
    new_client->socket_data = 0;
    bzero(&new_client->data_process, PARALLEL_PROCESS * sizeof(pid_t));
    new_client->sending = tcp_new_message();
    new_client->received = tcp_new_message();
    if (new_client->sending == NULL) {
        free(new_client);
        return (NULL);
    }
    new_client->quit = false;
    return (new_client);
}