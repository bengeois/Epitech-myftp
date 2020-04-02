/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"
#include <stdarg.h>

void add_message_client(client_t *client, char *str, ...)
{
    va_list ap;
    char message[TCP_MSGBUFF_SIZE];

    bzero(&message, TCP_MSGBUFF_SIZE);

    va_start(ap, str);
    vsprintf(message, str, ap);
    va_end(ap);

    tcp_add_to_message(client->sending, message);
}