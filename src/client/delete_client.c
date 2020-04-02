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
    free(real_data);
}