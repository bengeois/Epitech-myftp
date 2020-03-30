/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

int running_server(server_info_t *info)
{
    while (1) {
        set_fd_set(info);
    }
    return (EXIT_SUCCESS);
}