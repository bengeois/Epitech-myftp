/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <signal.h>
#include "myftp.h"

int myftp(int argc, char **argv)
{
    server_info_t *info = init_server_info();

    signal(SIGINT, &stop_server);
    server_stop = false;
    if (get_user_info(argc, argv, info) == EXIT_ERROR)
        return (exit_properly(info, EXIT_ERROR));

    if (start_server(info) == EXIT_ERROR)
        return (exit_properly(info, EXIT_ERROR));

    if (running_server(info) == EXIT_ERROR)
        return (exit_properly(info, EXIT_ERROR));

    return (exit_properly(info, EXIT_SUCCESS));
}