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
        perror("[SERVER] accept");
        return (EXIT_SUCCESS);
    }
    new_client->addr = new_client_addr;
    return (EXIT_SUCCESS);
}

int is_new_client(server_info_t *info)
{
    client_t *new = NULL;

    if (!FD_ISSET(info->server_socket, &info->read_fd))
        return (EXIT_SUCCESS);
    if ((new = new_client()) == NULL) {
        fprintf(stderr, "[SERVER] Client error.\n");
        return (EXIT_SUCCESS);
    }
    if (get_new_client_info(info, new) == EXIT_FAILURE) {
        free(new);
        return (EXIT_SUCCESS);
    }
    if (!list_add_elem_at_back(&info->clients, new)) {
        free(new);
        fprintf(stderr, "[SERVER] Client error.\n");
        return (EXIT_SUCCESS);
    }
    fprintf(stdout, "Client from %s:%i\n", inet_ntoa(new->addr
    .sin_addr), ntohs(new->addr.sin_port));
    add_message_client(new, E_220);
    return (EXIT_SUCCESS);
}