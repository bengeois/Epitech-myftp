/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <arpa/inet.h>
#include "myftp.h"

int start_server(server_info_t *info)
{
    if ((info->server_socket = create_socket()) == -1)
        return (EXIT_ERROR);
    info->address.sin_family = AF_INET;
    info->address.sin_port = htons(info->port);
    if (inet_pton(AF_INET, SERVER_IP, &info->address.sin_addr) <= 0) {
        perror("[Server] ip address");
        return (EXIT_ERROR);
    }
    if (bind(info->server_socket, (struct sockaddr *)&info->address, sizeof
    (info->address)) < 0) {
        perror("[Server] port");
        return (EXIT_ERROR);
    }
    if (listen(info->server_socket, LISTEN_CLIENT_QUEUE) < 0) {
        perror("[Server] listening");
        return (EXIT_ERROR);
    }
    fprintf(stdout, "Server is listening on %s:%i\n", SERVER_IP, ntohs
    (info->address.sin_port));
    return (EXIT_SUCCESS);
}