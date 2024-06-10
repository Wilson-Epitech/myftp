/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** handle_pwd
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "server.h"

void handle_pwd_command(server_t *server, cli_t *cli, char **array)
{
    if (strcmp(array[0], "PWD") == 0 && array[1] != NULL) {
        send_reply(server->sd, "500");
        return;
    }
    if (strcmp(array[0], "PWD") == 0)
        dprintf(server->sd, "257 %s\n", cli->working_dir);
    return;
}
