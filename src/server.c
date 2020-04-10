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
        &option, sizeof(option))) {
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
}

void start_server(server_t *server)
{
	int fd_client = 0;
	socklen_t len_cin = sizeof(server->inf);
	char *str = malloc(256);

    init_server(server);
    while (1) {
        init_sets(server);
        if ((select(FD_SETSIZE, &server->set[READING], 
            &server->set[WRITING], NULL, NULL)) == -1)
            break;

		if (FD_ISSET(server->fd_server, &server->set[READING])) {
	        fd_client = accept(server->fd_server, (struct sockaddr*)&server->inf, &len_cin);
	        dprintf(fd_client, "Hello world\n");
            read(fd_client, str, 256);
			printf("Client said : %s", str);
	        close(fd_client);
        }

    }
}