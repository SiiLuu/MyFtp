/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** ftp
*/

#ifndef FTP_H_
#define FTP_H_

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>

#define MAX_CLIENT 10
#define READING 0
#define WRITING 1

typedef struct clients_s {

    int fd_client;
    int nb_client;

}clients_t;

typedef struct server_s {

    int port;
    char *path;
    struct sockaddr_in inf;
    int fd_server;
    fd_set set[2];
    clients_t *clients;

}server_t;

void help();
void error_handling(int, char**);
void init_server(server_t*);
void init_sets(server_t *);
void start_server(server_t*);

#endif /* !FTP_H_ */
