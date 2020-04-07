/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include <wait.h>
#include "myftp.h"

int wait_data_process(client_t *client)
{
    int status;
    int check;
    for (int i = 0; i < PARALLEL_PROCESS && client->data_process[i] != 0; i++) {
        check = waitpid(client->data_process[i], &status, WNOHANG);
        if (check == client->data_process[i]) {
            close_fd(&client->socket_data);
            close_fd(&client->socket_mode);
            client->data_process[i] = 0;
            client->mode = UNDEFINED_MODE;
            add_message_client(client, E_226);
        }
    }
    return (EXIT_SUCCESS);
}