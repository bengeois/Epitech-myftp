/*
** EPITECH PROJECT, 2020
** my_ftp
** File description:
** TODO: add description
*/

#include "generic_list.h"

bool list_delete_node(node_t *node)
{
    if (!node) return (true);
    free(node);
    return (true);
}