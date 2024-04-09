/*
** MYFTP PROJECT, 2024
** [Conteneur de développement : C @ desktop-linux]
** File description:
** server
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

static void get_user_command(server_t *server, cli_t *cli, char **array, int i)
{
    if (strcmp(array[0], "QUIT") == 0) {
        close(server->sd);
        server->client_socket[i] = 0;
    }
    if ((strcmp(array[0], "USER") == 0))
        send_reply(server->sd, "331");
    if ((strcmp(array[0], "USER") == 0)
        && (strcmp(array[1], "Anonymous") == 0))
        cli[i].Anonymous_logged = 1;
    if ((strcmp(array[0], "PASS") == 0)
        && cli[i].Anonymous_logged == 1 && array[1] != NULL)
        send_reply(server->sd, "530");
    if ((strcmp(array[0], "PASS") == 0)
        && cli[i].Anonymous_logged == 1 && array[1] == NULL)
        send_reply(server->sd, "230");
}

static int check_usr_command(server_t *server, cli_t *cli, char *buffer, int i)
{
    char **commands = NULL;
    char **array = my_word_array_delim(buffer, " ");

    commands = init_array_commands(commands);
    if (array[1] == NULL && strcmp(array[0], "QUIT")
        != 0 && strcmp(array[0], "PASS") != 0) {
            return 1;
    }
    for (int j = 0; commands[j] != NULL; j++) {
        if (strcmp(array[0], commands[j]) == 0) {
            get_user_command(server, cli, array, i);
            return 0;
        }
    }
    return 1;
}

static void check_state(server_t *server, cli_t *cli, int i)
{
    int pos = 0;
    char *message = get_reply_code("500");

    server->valread = read(server->sd, server->buffer, 4096);
    if (server->valread == 0) {
        close(server->sd);
        server->client_socket[i] = 0;
    } else {
        server->buffer[server->valread - 2] = '\0';
        pos = check_usr_command(server, cli, server->buffer, i);
        if (pos == 1)
            write(server->sd, message, strlen(message));
    }
}

static void after_connection(server_t *server, cli_t *cli)
{
    for (int i = 0; i < server->max_clients; i++) {
        server->sd = server->client_socket[i];
        if (FD_ISSET(server->sd, &server->readfds)) {
            check_state(server, cli, i);
        }
    }
}

static void accept_connection(server_t *server)
{
    char *message = get_reply_code("220");

    server->nw_socket = accept(server->frst_socket,
        (struct sockaddr *)&server->socket, (socklen_t *)&server->socketlen);
    if (server->nw_socket < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    if (write(server->nw_socket, message,
        strlen(message)) != strlen(message)) {
        perror("write failed");
        exit(EXIT_FAILURE);
    }
}

int server_loop(server_t *server, cli_t *cli)
{
    init_server(server);
    process_socket(server);
    while (1) {
        FD_ZERO(&server->readfds);
        FD_SET(server->frst_socket, &server->readfds);
        server->max_sd = server->frst_socket;
        handle_client_socket(server);
        if ((select(server->max_sd + 1, &server->readfds,
            NULL, NULL, &server->timeout)) < 0) {
            perror("select failed");
            exit(EXIT_FAILURE);
        }
        if (FD_ISSET(server->frst_socket, &server->readfds)) {
            accept_connection(server);
            add_to_socket_list(server);
        }
        after_connection(server, cli);
    }
    return 0;
}
