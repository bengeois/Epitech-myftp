/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <zconf.h>
#include "myftp.h"

int arg_error(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        fprintf(stdout, "USAGE: %s port path\n", argv[0]);
        fprintf(stdout, "\tport  is the port number on which the server "
                        "socket listens\n");
        fprintf(stdout, "\tpath  is the path to the home directory for the "
                        "Anonymous user\n");
        return (EXIT_ERROR);
    }
    if (argc != 3) {
        fprintf(stderr, "%s: invalid command.\n", argv[0]);
        return (EXIT_ERROR);
    }
    return (EXIT_SUCCESS);
}

int get_user_info(int argc, char **argv, server_info_t *info)
{
    if (arg_error(argc, argv) == EXIT_ERROR)
        return (EXIT_ERROR);

    errno = 0;
    info->port = atoi(argv[1]);
    if (!info->port) {
        fprintf(stderr, "%s: invalid port number\n", argv[0]);
        return (EXIT_ERROR);
    }
    if (access(argv[2], F_OK) == -1) {
        fprintf(stderr, "%s: invalid home path\n", argv[0]);
        return (EXIT_ERROR);
    }
    info->anonymous_home = argv[2];
    return (EXIT_SUCCESS);
}