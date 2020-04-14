/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** read_client
*/

#include "ftp.h"

void new_clients(server_t *server)
{
	socklen_t len_cin = sizeof(server->inf);

    server->clients[server->nb_client].fd_client =
        accept(server->fd_server, (struct sockaddr*)&server->inf, &len_cin);
    server->clients[server->nb_client].real_path = strdup(server->path);
    server->clients[server->nb_client].path = strdup("/");
	dprintf(server->clients[server->nb_client].fd_client,
        "220 Service ready for new user\r\n");
	printf("New connection\r\n");
    server->nb_client++;  
}

void remove_client(server_t *server, int client, int id)
{
    while (id + 1 < server->nb_client) {
        server->clients[id] = server->clients[id + 1];
        id++;
    }
    close(client);
    server->nb_client--;
    printf("Client disconnected\r\n");
}

void old_clients(server_t *server, int client)
{
    server->command = calloc(0, 256);
    for (int i = 0; i < server->nb_client; i++) {
        if (server->clients[i].fd_client == client) {
            read(server->clients[i].fd_client, server->command, 256);
            exec_commands(server, server->clients[i].fd_client, i);
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
