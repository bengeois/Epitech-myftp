/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <arpa/inet.h>
#include "myftp.h"

int write_activity(server_info_t *info, node_t **temp)
{
    if (tcp_send_message(((client_t*)(*temp)->value)->socket, ((client_t*)
    (*temp)->value)->sending) == TCP_DISCONNECT) {
        disconnect_client(info, temp, "Client disconnected");
        return (LOOP_CONTINUE);
    }
    return (TCP_OK);
}

int read_activity(server_info_t *info, node_t **temp)
{
    if ((tcp_receive_message(((client_t*)(*temp)->value)->socket, ((client_t*)
    (*temp)->value)->received)) == TCP_DISCONNECT) {
        disconnect_client(info, temp, "Client disconnected");
        return (LOOP_CONTINUE);
    }
    return (TCP_OK);
}

int io_activities(server_info_t *info, node_t **temp)
{
    if (FD_ISSET(((client_t*)(*temp)->value)->socket, &info->except_fd)) {
        disconnect_client(info, temp, "Client Exception");
        return (LOOP_CONTINUE);
    }
    if (FD_ISSET(((client_t*)(*temp)->value)->socket, &info->write_fd)) {
        if (write_activity(info, temp) == LOOP_CONTINUE)
            return (LOOP_CONTINUE);
    }
    if (FD_ISSET(((client_t*)(*temp)->value)->socket, &info->read_fd)) {
        if (read_activity(info, temp) == LOOP_CONTINUE)
            return (LOOP_CONTINUE);
    }
    return (EXIT_SUCCESS);
}

int handle_socket_activities(server_info_t *info)
{
    node_t *temp = info->clients;
    while (temp) {
        if (io_activities(info, &temp) == LOOP_CONTINUE)
            continue;
        temp = temp->next;
    }
    return (TCP_OK);
}