/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** main
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "server.h"

static int error_handling(server_t *server, int ac, char **av)
{
    if (ac != 3) {
        printf("bad option, run ./myftp -help\n");
        return FAILURE;
    }
    if (get_args(server, av) == 84)
        return FAILURE;
    if (chdir(server->path) != 0) {
        printf("Directory doesn't exsist\n");
        return FAILURE;
    }
    return SUCCESS;
}

int main(int ac, char **av)
{
    server_t *server = malloc(sizeof(server_t));
    cli_t *cli = malloc(sizeof(cli_t) * (30));
    const char *usage = "USAGE: ./myftp port path\n"
        "port is the port number on which the server socket listens\n"
        "path is the path to the home directory for the Anonymous user\n";

    memset(server, 0, sizeof(server_t));
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("%s", usage);
        return SUCCESS;
    }
    if (error_handling(server, ac, av) == 84)
        return FAILURE;
    server_loop(server, cli);
    return SUCCESS;
}
