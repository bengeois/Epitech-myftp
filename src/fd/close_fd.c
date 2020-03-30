/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <zconf.h>

void close_fd(int *fd)
{
    if (*fd == -1)
        return;
    close(*fd);
    *fd = -1;
}