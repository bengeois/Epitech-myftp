/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

void manage_timeout_select(struct timeval *timeout)
{
    timeout->tv_sec = 0;
    timeout->tv_usec = 500000;
}