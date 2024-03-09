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
    socklen_t socketlen;
    char *buffer;
    int fd;
    int nw_socket;
    fd_set readfds;
    struct timeval timeout;
} server_t;

int server_loop(server_t *server);
void init_sockstruct(server_t *server);
int init_socket(int fd);

#endif /* !SERVER_H_ */
