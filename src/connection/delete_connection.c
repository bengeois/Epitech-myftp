/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

void delete_connection(void *data)
{
    if (!data)
        return;
    connection_t *real_data = (connection_t*)data;
    free(real_data);
}