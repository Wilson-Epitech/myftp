/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** handle_cwd
*/

#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <libgen.h>
#include "server.h"

static int is_dir(const char *filename)
{
    struct stat path;

    if (stat(filename, &path) == 0 && S_ISDIR(path.st_mode))
        return 1;
    return 0;
}

static char *update_path(char *current_path, char *dirname)
{
    char *new_path = NULL;

    new_path = strdup(current_path);
    strcat(new_path, "/");
    strcat(new_path, dirname);
    return new_path;
}

static int count_backward(char *str)
{
    int z = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '/')
            z++;
    }
    return z;
}

static void backward_path(server_t *server, cli_t *cli, int value, int i)
{
    char *tmp = NULL;

    for (int n = 0; n < value; n++) {
        tmp = dirname(cli[i].working_dir);
        cli[i].working_dir = tmp;
    }
    send_reply(server->sd, "250");
}

static void handle_cdup_command(server_t *server,
    cli_t *cli, char **array, int i)
{
    if (strcmp(array[0], "CDUP") == 0) {
        backward_path(server, cli, 1, i);
    }
}

static void handle_cwd_command(server_t *server,
    cli_t *cli, char **array, int i)
{
    int tmp = 0;
    char *next_dir = NULL;

    if (strcmp(array[0], "CWD") == 0 && array[1] == NULL) {
        send_reply(server->sd, "550");
        return;
    }
    if (strcmp(array[0], "CWD") == 0 && array[1] != NULL) {
        next_dir = update_path(cli[i].working_dir, array[1]);
        tmp = is_dir(next_dir);
        if (strncmp(array[1], "../", 3) == 0) {
            backward_path(server, cli, count_backward(array[1]), i);
            return;
        }
        if (tmp == 0) {
            send_reply(server->sd, "550");
            return;
        } else {
            cli[i].working_dir = update_path(cli[i].working_dir, array[1]);
            send_reply(server->sd, "250");
        }
    }
}

void handle_cwd_cdup_command(server_t *server, cli_t *cli, char **array, int i)
{
    handle_cwd_command(server, cli, array, i);
    handle_cdup_command(server, cli, array, i);
}
