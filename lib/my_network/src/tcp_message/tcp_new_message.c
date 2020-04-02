/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "my_network.h"

message_t *tcp_new_message(void)
{
    message_t *message = malloc(sizeof(message_t));

    if (!message)
        return (NULL);
    bzero(message->buff, TCP_MSGBUFF_SIZE + 1);
    message->write_pos = 0;
    message->sending_pos = 0;
    return (message);
}