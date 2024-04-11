/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** handle_cwd
*/

#include <string.h>
#include <stdio.h>
#include "server.h"

void handle_cwd_command(server_t *server, cli_t *cli, char **array, int i)
{
    if (strcmp(array[0], "CWD") == 0 && array[1] != NULL) {
        if (chdir(array[1]) != 0) {
            send_reply(server->sd, "550");
            return;
        } else {
            cli[i].working_dir = array[1];
            send_reply(server->sd, "250");
        }
    }
}