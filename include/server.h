/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** server
*/

#include <netinet/ip.h>

#ifndef SERVER_H_
    #define SERVER_H_

typedef struct server_s {
    struct sockaddr_in socket;
    struct sockaddr_in dataSocket;
    int port;
    char *path;
    socklen_t socketlen;
    char *buffer;
    char *data_buffer;
    int fd;
    int nw_socket;
    int nw_data_socket;
    int fd_data;
    fd_set readfds;
    struct timeval timeout;
} server_t;

int server_loop(server_t *server);
void init_sock_struct(server_t *server);
int init_socket(int fd);
void init_data_struct(server_t *server);
int get_args(server_t *server, char **av);
void data_socket_loop(server_t *server);

#endif /* !SERVER_H_ */
