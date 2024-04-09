/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** handle_pass
*/

#include "server.h"
#include <string.h>
// put anonymous_logged at 0 when the client give the wrong
// password for anonymous user because we can't use
// the command PASS two consecutives times.
// ---------------------------------------------------------------------
// put other_user at 0 when the client give the wrong
// password for user because we can't use the command PASS
// two consecutives times.

void handle_pass_command(server_t *server, cli_t *cli, char **array, int i)
{
    if (strcmp(array[0], "PASS") == 0
        && (cli[i].anonymous_logged == 0 && cli[i].other_user == 0))
        send_reply(server->sd, "503");
    if ((strcmp(array[0], "PASS") == 0)
        && cli[i].anonymous_logged == 1 && array[1] != NULL) {
        send_reply(server->sd, "530");
        cli[i].anonymous_logged = 0;
    }
    if (strcmp(array[0], "PASS") == 0 && cli[i].other_user == 1) {
        send_reply(server->sd, "530");
        cli[i].other_user = 0;
    }
    if ((strcmp(array[0], "PASS") == 0)
        && cli[i].anonymous_logged == 1 && array[1] == NULL)
        send_reply(server->sd, "230");
}
