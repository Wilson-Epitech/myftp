/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** handle_noop
*/

#include "server.h"
#include <string.h>

void handle_noop_command(server_t *server, char **array)
{
    if (strcmp(array[0], "NOOP") == 0) {
        send_reply(server->sd, "200");
    }
}
