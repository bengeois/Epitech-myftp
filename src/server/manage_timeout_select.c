/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

void manage_timeout_select(server_info_t *info)
{
    info->timeout.tv_sec = 2;
}