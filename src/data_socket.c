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