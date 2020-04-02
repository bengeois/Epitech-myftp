/*
** EPITECH PROJECT, 2018
** my.h
** File description:
** libmy header
*/

#ifndef MY_NETWORK_H
#define MY_NETWORK_H

#include <stdlib.h>
#include <string.h>
#include <zconf.h>
#include <stdbool.h>

/**************************************
 * DEFINE DEFINITION
 *************************************/

#define TCP_MSGBUFF_SIZE 10000
#define TCP_READ_SIZE 1

#define TCP_OK 0
#define TCP_ERROR -1
#define TCP_DISCONNECT -2


/**************************************
 * STRUCTURE DEFINITION
 *************************************/

typedef struct message_s
{
    char buff[TCP_MSGBUFF_SIZE + 1];
    int write_pos;
    int sending_pos;
} message_t;

/**************************************
 * FUNCTION DEFINITION
 *************************************/

/* MESSAGE*/
message_t *tcp_new_message(void);
int tcp_add_to_message(message_t *message, char *str);
int tcp_send_message(int socket, message_t *message);
bool tcp_is_waiting_message(message_t *message);
char *tcp_get_message2(char *line, char *buffer, int i, int j);
char *tcp_get_message(int socket);

/* SOCKET */
int create_socket(void);

#endif
