/*
** MYFTP PROJECT, 2024
** [Conteneur de développement : C @ desktop-linux]
** File description:
** init
*/

#include <stdlib.h>
#include <stdio.h>
#include "server.h"

void init_sockstruct(server_t *server)
{
    server->socket.sin_family = AF_INET;
    server->socket.sin_addr.s_addr = INADDR_ANY;
    server->socket.sin_port = htons(4242);
}

int init_socket(int fd)
{
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    return fd;
}
