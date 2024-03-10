/*
** MYFTP PROJECT, 2024
** [Conteneur de développement : C @ desktop-linux]
** File description:
** server
*/

#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include "server.h"

static void get_retr_path(server_t *server)
{
    printf("ici buffer retr %s\n", server->buffer);
}

static void process_socket(server_t *server)
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

static void accept_connection(server_t *server)
{
    server->nw_socket = accept(server->fd, (struct sockaddr*)
        &server->socket, &server->socketlen);
    if (server->nw_socket < 0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
}

static void after_connection(server_t *server)
{
    read(server->nw_socket, server->buffer, 1024 - 1);
    if (strstr(server->buffer, "PASV") != NULL) {
        data_socket_loop(server);
    }
    if (strstr(server->buffer, "RETR") != NULL) {
        get_retr_path(server);
    }
    puts(server->buffer);
}

int server_loop(server_t *server)
{
    server->buffer = malloc(sizeof(char) * 1024);
    server->socketlen = sizeof(server->socket);
    server->fd = init_socket(server->fd);
    init_sock_struct(server);
    process_socket(server);
    while (1) {
        FD_ZERO(&server->readfds);
        FD_SET(server->fd, &server->readfds);
        if ((select(server->fd + 1, &server->readfds,
            NULL, NULL, &server->timeout)) < 0) {
            perror("select failed");
            exit(EXIT_FAILURE);
        }
        if (FD_ISSET(server->fd, &server->readfds)) {
            accept_connection(server);
            after_connection(server);
        }
    }
    close(server->fd);
    return 0;
}
