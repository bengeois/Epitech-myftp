/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** TODO: add description
*/

#include "myftp.h"

int get_size_array(char **array)
{
    int i = 0;

    while (array != NULL && array[i] != NULL) {
        i++;
    }
    return i;
}
