/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <arpa/inet.h>
#include <ctype.h>
#include "myftp.h"

static bool check_info_ip(char **info_ip)
{
    for (int i = 0; i < get_size_array(info_ip); i++) {
        for (size_t j = 0; j < strlen(info_ip[i]); j++) {
            if (!isdigit(info_ip[i][j]))
                return (false);
        }
    }
    return (true);
}

static int get_connect_port_info(client_t *client, char *info)
{
    char **info_ip = my_strtok(info, ',');
    char ip[200];

    if (!info_ip || get_size_array(info_ip) < 6 || !check_info_ip(info_ip)) {
        free_array(info_ip);
        return (TCP_ERROR);
    }
    if ((client->socket_data = create_socket()) == TCP_ERROR)
        return (TCP_ERROR);
    bzero(ip, 200);
    client->data_addr.sin_family = AF_INET;
    client->data_addr.sin_port = htons(atoi(info_ip[4]) * 256 + atoi(info_ip[5]));
    strcpy(ip, info_ip[0]);
    for (int i = 1; i < 4; i++) {
        strcat(ip, ".");
        strcat(ip, info_ip[i]);
    }
    free(info_ip);
    if (inet_pton(AF_INET, ip, &client->data_addr.sin_addr) <= 0)
        return (TCP_ERROR);
    return (TCP_OK);
}

void port(server_info_t *info, client_t *client, char **cmd)
{
    (void)info;
    if (is_client_login(client) != LOGGED)
        return (add_message_client(client, E_530PL));
    if (get_size_array(cmd) < 2)
        return (add_message_client(client, E_501));
    if (client->mode == ACTIVE)
        close_fd(&client->socket_data);
    if (get_connect_port_info(client, cmd[1]) == TCP_ERROR)
        return (add_message_client(client, E_501));
    client->mode = ACTIVE;
    return (add_message_client(client, E_200));
}