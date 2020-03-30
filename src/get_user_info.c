/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <stdio.h>
#include <string.h>
#include "myftp.h"

int get_user_info(int argc, char **argv, server_info_t *info)
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
    (void)info;
    return (0);
}