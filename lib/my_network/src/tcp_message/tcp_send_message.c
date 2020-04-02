/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "my_network.h"

int tcp_send_message(int socket, message_t *message)
{
    int sending_byte = 0;

    if (message->buff[message->sending_pos] == 0)
        return (TCP_OK);

    while ((sending_byte = write(socket, &message->buff[message->sending_pos],
    strlen(&message->buff[message->sending_pos]))) > 0) {

        bzero(&message->buff[message->sending_pos], sending_byte);
        message->sending_pos += sending_byte;
        if (message->sending_pos >= TCP_MSGBUFF_SIZE)
            message->sending_pos = 0;
        if (message->buff[message->sending_pos] == 0)
            break;
    }
    if (sending_byte == -1)
        return (TCP_DISCONNECT);
    return (TCP_OK);
}