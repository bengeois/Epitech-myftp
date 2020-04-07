/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <arpa/inet.h>
#include "myftp.h"

static int create_passive_mode(server_info_t *info, client_t *client)
{
    socklen_t size;
    if ((client->socket_mode = create_socket()) == TCP_ERROR)
        return (TCP_ERROR);
    client->data_addr = info->address;
    client->data_addr.sin_port = 0;
    if (inet_pton(AF_INET, SERVER_IP, &client->data_addr.sin_addr) <= 0)
        return (TCP_ERROR);
    if (bind(client->socket_mode, (struct sockaddr *)&client->data_addr, sizeof
        (client->data_addr)) < 0)
        return (TCP_ERROR);
    if (listen(client->socket_mode, LISTEN_CLIENT_QUEUE) < 0)
        return (TCP_ERROR);
    size = sizeof(client->data_addr);
    if (getsockname(client->socket_mode, (struct sockaddr *)
        &client->data_addr, &size) == -1)
        return (TCP_ERROR);
    return (TCP_OK);
}

static void print_passive_info(client_t *client)
{
    add_message_client(client, E_227, (client->data_addr.sin_addr.s_addr >>
    (8*0)) & 0xff, (client->data_addr.sin_addr.s_addr >> (8*1)) & 0xff,
    (client->data_addr.sin_addr.s_addr >> (8*2)) & 0xff,
    (client->data_addr.sin_addr.s_addr >> (8*3)) & 0xff, ntohs(client->data_addr
    .sin_port) / 256, ntohs(client->data_addr.sin_port) % 256);
}

void pasv(server_info_t *info, client_t *client, char **cmd)
{
    (void)cmd;
    if (is_client_login(client) != LOGGED)
        return (add_message_client(client, E_530PL));
    if (client->mode == PASSIVE)
        close_fd(&client->socket_mode);
    if (create_passive_mode(info, client) == TCP_ERROR) {
        close_fd(&client->socket_mode);
        return (add_message_client(client, E_425));
    }
    client->mode = PASSIVE;
    print_passive_info(client);
}