/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <arpa/inet.h>
#include "myftp.h"

int get_new_client_info(server_info_t *info, client_t *new_client)
{
    struct sockaddr_in new_client_addr;
    int new_client_addr_len;

    bzero(&new_client_addr, sizeof(struct sockaddr_in));
    new_client_addr_len = sizeof(new_client_addr);
    if ((new_client->socket = accept(info->server_socket, (struct sockaddr *)
    &new_client_addr, (socklen_t *) &new_client_addr_len)) < 0) {
        perror("[SERVER] client refused");
        return (TCP_ERROR);
    }
    new_client->addr = new_client_addr;
    return (TCP_OK);
}

int is_new_client(server_info_t *info)
{
    client_t *new = NULL;

    if (!FD_ISSET(info->server_socket, &info->read_fd))
        return (TCP_OK);
    if ((new = new_client()) == NULL) {
        fprintf(stderr, "[SERVER] Client error.\n");
        return (TCP_OK);
    }
    if (get_new_client_info(info, new) == TCP_ERROR) {
        free(new);
        return (TCP_OK);
    }
    if (!list_add_elem_at_back(&info->clients, new)) {
        free(new);
        fprintf(stderr, "[SERVER] Client error. Retry\n");
        return (TCP_OK);
    }
    fprintf(stdout, "Client from %s:%i\n", inet_ntoa(new->addr
    .sin_addr), ntohs(new->addr.sin_port));
    add_message_client(new, E_220);
    return (TCP_OK);
}