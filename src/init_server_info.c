/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include "myftp.h"

server_info_t *init_server_info(void)
{
    server_info_t *info = malloc(sizeof(server_info_t));

    if (!info) {
        fprintf(stderr, "malloc() failed\n");
        return (NULL);
    }
    info->port = -1;
    info->anonymous_home = NULL;
    return (info);
}