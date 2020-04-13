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

void new_clients(server_t *server)
{
	socklen_t len_cin = sizeof(server->inf);

    server->clients[server->nb_client].fd_client =
        accept(server->fd_server, (struct sockaddr*)&server->inf, &len_cin);
	dprintf(server->clients[server->nb_client].fd_client,
        "220 Connected.\r\n");
	printf("New connection\r\n");
    server->nb_client++;  
}

void remove_client(server_t *server, int client, int id)
{
    printf("%d, %d\r\n", id, server->nb_client);
    while (id + 1 < server->nb_client) {
        server->clients[id] = server->clients[id + 1];
        id++;
    }
    close(client);
    printf("Client : %d\r\n", server->nb_client);
    server->nb_client--;
    printf("Client : %d\r\n", server->nb_client);
    printf("Client deconnected\r\n");
}

void old_clients(server_t *server, int client)
{
	char *str = malloc(256);

    for (int i = 0; i < server->nb_client; i++) {
        if (server->clients[i].fd_client == client) {
            free(str);
            read(server->clients[i].fd_client, str, 256);
            if (strcmp(str, "QUIT\r\n") == 0) {
                dprintf(server->clients[i].fd_client, "221 Goodbye\r\n");
                remove_client(server, server->clients[i].fd_client, i);
            }
            else {
                dprintf(server->clients[i].fd_client, "TAMER\r\n");
            }
        }
    }
}

void reading(server_t *server)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(i, &server->set[READING]) == true) {
            if (i == server->fd_server) {
                new_clients(server);
            }
            else {
                old_clients(server, i);
            }
        }
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