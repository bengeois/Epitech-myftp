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
    size_t needed = 0;
    char *message = NULL;

    va_start(ap, str);
    needed = vsnprintf(NULL, 0, str, ap) + 1;
    va_end(ap);

    message = calloc(needed + 1, sizeof(char));

    if (!message) return;

    va_start(ap, str);
    vsprintf(message, str, ap);
    va_end(ap);

    vsprintf(message, str, ap);
    tcp_add_to_message(client->sending, message);
    //list_add_elem_at_back(&client->sending, message);
}