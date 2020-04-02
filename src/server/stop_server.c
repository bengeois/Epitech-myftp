/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

void stop_server(int signal)
{
    (void)signal;
    server_stop = true;
}