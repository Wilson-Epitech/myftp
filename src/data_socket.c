/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** dataSocket
*/

#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

static void reply227(server_t *server)
{
    char *str = "227 Entering Passive Mode";
    char *addr = inet_ntoa(server->dataSocket.sin_addr);
    int port = ntohs(server->dataSocket.sin_port);
    size_t length = strlen(str) + strlen(addr) + 7 + 1;
    char *answer = malloc(length);
    char *token;
    int ip[4];
    int i = 0;

    token = strtok(addr, ".");
    while (token != NULL && i < 4) {
        ip[i] = atoi(token);
        token = strtok(NULL, ".");
        i++;
    }
    sprintf(answer, "%s (%d,%d,%d,%d,%d,%d)\n", str, ip[0], ip[1], ip[2],
        ip[3], port / 256, port % 256);
    send(server->nw_socket, answer, strlen(answer), 0);
    free(answer);
}

static void create_data_socket(server_t *server)
{
    server->fd_data = init_socket(server->fd_data);
    init_data_struct(server);
    if (bind(server->fd_data, (struct sockaddr*) &server->dataSocket,
        sizeof(server->dataSocket)) < 0) {
        perror("bind data failed");
        exit(EXIT_FAILURE);
    }
}
