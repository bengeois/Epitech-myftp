/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <arpa/inet.h>
#include "myftp.h"

int get_new_client_info(server_info_t *info, connection_t *new_client)
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
    connection_t *new_client = NULL;

    if (!FD_ISSET(info->server_socket, &info->read_fd))
        return (EXIT_SUCCESS);
    if ((new_client = new_connection()) == NULL) {
        fprintf(stderr, "[SERVER] Connection error.\n");
        return (EXIT_SUCCESS);
    }
    if (get_new_client_info(info, new_client) == EXIT_FAILURE) {
        free(new_client);
        return (EXIT_SUCCESS);
    }
    if (!list_add_elem_at_back(&info->connections, new_client)) {
        free(new_client);
        fprintf(stderr, "[SERVER] Connection error.\n");
        return (EXIT_SUCCESS);
    }
    fprintf(stdout, "Connection from %s:%i\n", inet_ntoa(new_client->addr
    .sin_addr), ntohs(new_client->addr.sin_port));
    return (EXIT_SUCCESS);
}