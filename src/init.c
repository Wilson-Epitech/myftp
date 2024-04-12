/*
** MYFTP PROJECT, 2024
** [Conteneur de développement : C @ desktop-linux]
** File description:
** init
*/

#include <stdlib.h>
#include <stdio.h>
#include "server.h"

char **init_array_reply(char **array)
{
    array = malloc(sizeof(char *) * (16));
    array[8] = "150 File status okay; about to open data connection.\n";
    array[5] = "200 Command okay.\n";
    array[11] = "214 Help message.\n";
    array[0] = "220 Service ready for new user.\n";
    array[6] = "221 Service closing control connection.\n";
    array[9] = "226 Closing data connection.\n";
    array[7] = "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\n";
    array[1] = "230 User logged in, proceed.\n";
    array[4] = "250 Requested file action okay, completed.\n";
    array[10] = "257 PATHNAME created.\n";
    array[2] = "331 User name okay, need password.\n";
    array[3] = "332 Need account for login.\n";
    array[12] = "500 Invalid command.\n";
    array[13] = "503 Bad sequence of commands.\n";
    array[14] = "530 Not logged in.\n";
    array[15] = "550 Requested action not taken.\n";
    array[16] = NULL;
    return array;
}

char **init_array_commands(char **array)
{
    array = malloc(sizeof(char *) * (14));
    array[0] = "USER";
    array[1] = "PASS";
    array[2] = "CWD";
    array[3] = "CDUP";
    array[4] = "QUIT";
    array[5] = "DEL";
    array[6] = "PWD";
    array[7] = "PASV";
    array[8] = "PORT";
    array[9] = "HELP";
    array[10] = "NOOP";
    array[11] = "RETR";
    array[12] = "STOR";
    array[13] = "LIST";
    array[14] = NULL;
    return array;
}

void init_sock_struct(server_t *server)
{
    server->socket.sin_family = AF_INET;
    server->socket.sin_addr.s_addr = INADDR_ANY;
    server->socket.sin_port = htons(server->port);
}

// void init_data_struct(server_t *server)
// {
//     server->dataSocket.sin_family = AF_INET;
//     server->dataSocket.sin_addr.s_addr = INADDR_ANY;
//     server->dataSocket.sin_port = htons(4343);
// }
void init_server(server_t *server)
{
    server->opt = 1;
    server->max_clients = 30;
    server->client_socket = malloc(sizeof(int) * (30));
    server->buffer = malloc(sizeof(char) * (4096));
    server->Anonymous_logged = 0;
    reset_client_socket(server);
    server->frst_socket = init_socket(server->frst_socket, server->opt);
    init_sock_struct(server);
}

int init_socket(int fd, int opt)
{
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
        sizeof(opt)) < 0) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }
    return fd;
}
