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
    {"QUIT", &quit, "Leave the server and close the client."},
    {"USER", &user, "Specify your username."},
    {"PASS", &pass, "Specify your password."},
    {"NOOP", &noop, "Do nothing."},
    {"HELP", &help, "List available commands."},
    {"PWD", &pwd, "Print working directory."},
    {"DELE", &dele, "Print working directory."},
    {"CWD", &cwd, "Change working directory."},
    {"CDUP", &cdup, "Change working to parent directory."},
    {"PASV", &pasv, "Entering passive mode."},
    {"PORT", &port, "Entering active mode."},
    {"LIST", &list, "List all files in working directory."},
    {"RETR", &retr, "Download file from server to client."},
    {"STOR", &stor, "Upload file from client to server."},
    {NULL, NULL, NULL}
};

#endif //NWP_MYFTP_2019_COMMANDS_H
