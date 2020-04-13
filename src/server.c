/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** server
*/

#include "ftp.h"

void init_server(server_t *server)
{
    int option = 1;
	socklen_t len = sizeof(server->inf);

    if ((server->fd_server = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket failed");
        exit(84);
    }
    if (setsockopt(server->fd_server, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
        &option, sizeof(int))) {
        perror("Setsockopt");
        exit(84);
    }
    server->inf.sin_addr.s_addr = htonl(INADDR_ANY);
	server->inf.sin_port = htons(server->port);
	server->inf.sin_family = AF_INET;
	if (bind(server->fd_server, (struct sockaddr*)&server->inf, len) < 0)
        exit(84);
	if (listen(server->fd_server, MAX_CLIENT) < 0)
        exit(84);
}

void init_sets(server_t *server)
{
    FD_ZERO(&server->set[READING]);
    FD_ZERO(&server->set[WRITING]);
    FD_SET(server->fd_server, &server->set[READING]);
	FD_SET(server->fd_server, &server->set[WRITING]);
    for (int i = 0; i < server->nb_client; i++) {
    	FD_SET(server->clients[i].fd_client, &server->set[READING]);
        FD_SET(server->clients[i].fd_client, &server->set[WRITING]);
    }
}

void start_server(server_t *server)
{
    init_server(server);
    while (1) {
        init_sets(server);
        if ((select(FD_SETSIZE, &server->set[READING], 
            &server->set[WRITING], NULL, NULL)) == -1)
            break;
        reading(server);
        //writing(server);
    }
}
