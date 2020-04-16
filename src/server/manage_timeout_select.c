/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

void manage_timeout_select(server_info_t *info, struct timeval *timeout)
{
    timeout->tv_sec = 0;
    timeout->tv_usec = 0;
    if (list_is_empty(info->clients))
        return;
    for (node_t *tmp = info->clients; tmp; tmp = tmp->next) {
        for (int i = 0; i < PARALLEL_PROCESS; i++) {
            if (((client_t*)tmp->value)->data_process[i] != 0) {
                timeout->tv_usec = 500000;
                return;
            }
        }
    }
}