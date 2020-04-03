/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#ifndef NWP_MYFTP_2019_COMMANDS_H
#define NWP_MYFTP_2019_COMMANDS_H

#include "myftp.h"

static const command_t commands[] =
    {
        {"QUIT", &quit, "Leave the server and close the client.\n"},
        {"USER", &user, "Specify your username.\n"},
        {"PASS", &pass, "Specify your password.\n"},
        {NULL, NULL, NULL}
    };

#endif //NWP_MYFTP_2019_COMMANDS_H
