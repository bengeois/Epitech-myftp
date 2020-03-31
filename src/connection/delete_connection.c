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

void delete_connection(void *data)
{
    if (!data)
        return;
    connection_t *real_data = (connection_t*)data;
    if (real_data->received)
        free(real_data->received);
    if (real_data->sending)
        list_clear(real_data->sending, delete_sending);
    free(real_data);
}