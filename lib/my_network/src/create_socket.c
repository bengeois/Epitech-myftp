/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <stdio.h>
#include <sys/socket.h>
#include "my_network.h"

int create_socket(void)
{
    int opt = 1;
    int new_socket = -1;
    if ((new_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("create_socket:");
        return (-1);
    }
    if (setsockopt(new_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
    sizeof(opt))) {
        perror("setsockopt");
        return (-1);
    }
    return (new_socket);
}