/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** main
*/

#include <netinet/ip.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

void init_sockstruct(server_t *server)
{
    server->socket.sin_family = AF_INET;
    server->socket.sin_addr.s_addr = INADDR_ANY;
    server->socket.sin_port = htons(4242);
}

int init_socket(int fd)
{
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    return fd; 
}

void process_socket(server_t *server)
{
    if (bind(server->fd, (struct sockaddr*) &server->socket,
        sizeof(server->socket)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server->fd, 100) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

void accept_connection(server_t *server)
{
    if ((server->nw_socket = accept(server->fd, (struct sockaddr*)
        &server->socket, &server->socketlen)) < 0) {
            perror("accept failed");
            exit(EXIT_FAILURE);
    }
}

int server_loop(server_t *server)
{
    server->buffer = malloc(sizeof(char) * 1024);
    server->socketlen = sizeof(server->socket);
    server->fd = init_socket(server->fd);
    init_sockstruct(server);
    process_socket(server);
    while (1) {
        fork();
        accept_connection(server);
        read(server->nw_socket, server->buffer, 1024 - 1);
        puts(server->buffer);
        send(server->nw_socket, "hello\n", 6, 0);
        close(server->nw_socket);
        sleep(10);
    }
    close(server->fd);
    return 0;
}

int main(int ac, char **av)
{
    server_t *server = malloc(sizeof(server_t));
    memset(server, 0, sizeof(server_t));
    const char *usage = "\nUSAGE: ./myftp port path\n"
        "port is the port number on which the server socket listens\n"
        "path is the path to the home directory for the Anonymous user\n";

    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("%s", usage);
        return 0;
    }
    server_loop(server);
    return 0;
}