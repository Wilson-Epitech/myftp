/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    typedef struct server_s {
        struct sockaddr_in socket;
        socklen_t socketlen;
        char *buffer;
        int fd;
        int nw_socket;
    }  server_t;

#endif /* !SERVER_H_ */
