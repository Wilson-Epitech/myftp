/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** socket
*/

#include "server.h"
#include <stdio.h>
#include <stdlib.h>

void process_socket(server_t *server)
{
    if (bind(server->frst_socket, (struct sockaddr *)&server->socket,
        sizeof(server->socket)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server->frst_socket, 100) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    server->socketlen = sizeof(server->socket);
}

void reset_client_socket(server_t *server)
{
    for (int i = 0; i < server->max_clients; i++) {
        server->client_socket[i] = 0;
    }
}

void handle_client_socket(server_t *server)
{
    for (int i = 0; i < server->max_clients; i++) {
        server->sd = server->client_socket[i];
        if (server->sd > 0)
            FD_SET(server->sd, &server->readfds);
        if (server->sd > server->max_sd)
            server->max_sd = server->sd;
    }
}

void add_to_socket_list(server_t *server)
{
    for (int i = 0; i < server->max_clients; i++) {
        if (server->client_socket[i] == 0) {
            server->client_socket[i] = server->nw_socket;
            break;
        }
    }
}
