/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

int myftp(int argc, char **argv)
{
    server_info_t *info = init_server_info();
    if (get_user_info(argc, argv, info) == EXIT_ERROR)
        return (EXIT_ERROR);
    return (EXIT_SUCCESS);
}