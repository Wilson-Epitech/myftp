/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** handle_user
*/

#include "server.h"
#include <string.h>

void handle_user_command(server_t *server, cli_t *cli, char **array, int i)
{
    if (strcmp(array[0], "USER") == 0 && array[1] == NULL)
        send_reply(server->sd, "332");
    if ((strcmp(array[0], "USER") == 0) && array[1] != NULL) {
        send_reply(server->sd, "331");
        cli[i].other_user = 1;
        cli[i].anonymous_logged = 0;
    }
    if ((strcmp(array[0], "USER") == 0)
        && array[1] != NULL && (strcmp(array[1], "Anonymous") == 0)) {
        cli[i].anonymous_logged = 1;
        cli[i].other_user = 0;
    }
}
