/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** handle_list
*/

#include <string.h>
#include "server.h"

void handle_list_command(server_t *server, cli_t *cli, char **array, int i)
{
    if (strcmp(array[0], "LIST") == 0)
        send_reply(server->sd, "425");
}
