/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** main
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

int main(int ac, char **av)
{
    server_t *server = malloc(sizeof(server_t));
    const char *usage = "USAGE: ./myftp port path\n"
        "port is the port number on which the server socket listens\n"
        "path is the path to the home directory for the Anonymous user\n";

    memset(server, 0, sizeof(server_t));
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("%s", usage);
        return 0;
    }
    if (ac != 3) {
        printf("bad option, run ./myftp -help\n");
        return 84;
    }
    if (get_args(server, av) == 84)
        return 84;
    server_loop(server);
    return 0;
}
