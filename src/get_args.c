/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** getArgs
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

static bool is_number(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

int get_args(server_t *server, char **av)
{
    if (!is_number(av[1]))
        return 84;
    server->port = atoi(av[1]);
    if (av[2][0] == '\0')
        return 84;
    if (is_number(av[2]))
        return 84;
    server->path = strdup(av[2]);
    return 0;
}
