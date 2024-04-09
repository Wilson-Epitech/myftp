/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** handle_quit
*/

#include "server.h"
#include <string.h>

void handle_quit_command(server_t *server, char **array, int i)
{
    if (strcmp(array[0], "QUIT") == 0) {
        close(server->sd);
        server->client_socket[i] = 0;
    }
}
