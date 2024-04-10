/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** handle_help
*/

#include "server.h"
#include <string.h>

void handle_help_command(server_t *server, char **array)
{
    if (strcmp(array[0], "HELP") == 0) {
        send_reply(server->sd, "214");
    }
}
