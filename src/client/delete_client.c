/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

void delete_sending(void *data)
{
    if (!data)
        return;
    free(data);
}

void delete_client(void *data)
{
    if (!data)
        return;
    client_t *real_data = (client_t*)data;
    if (real_data->received)
        free(real_data->received);
    if (real_data->sending)
        free(real_data->sending);
    if (real_data->username)
        free(real_data->username);
    if (real_data->passwd)
        free(real_data->passwd);
    close_fd(&real_data->socket_mode);
    close_fd(&real_data->socket_data);
    free(real_data);
}