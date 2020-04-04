/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

int add_process_to_client(client_t *client, pid_t to_add)
{
    int i = 0;
    for (i = 0; client->data_process[i] != 0 && i < PARALLEL_PROCESS; i++);
    client->data_process[i] = to_add;
    return (EXIT_SUCCESS);
}