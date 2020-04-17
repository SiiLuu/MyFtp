/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** passive_mode
*/

#include "ftp.h"

void find_port(int dt_socket, int *port1, int *port2)
{
    struct sockaddr_in inf;
    socklen_t len = sizeof(inf);

    if (*port2 < 255)
        *port2 += 1;
    else if (*port1 < 255)
        *port1 += 1;
    else
        return;
    inf.sin_addr.s_addr = htonl(INADDR_ANY);
    inf.sin_family = AF_INET;
    inf.sin_port = htons(*port1 * 256 + *port2);
    if (bind(dt_socket, (struct sockaddr *)&inf, len) == -1)
        find_port(dt_socket, port1, port2);
}

void data_socket(server_t *server, int client, int id)
{
    int port1 = 5;
    int port2 = 4;
    int dt_socket = socket(AF_INET, SOCK_STREAM, 0);

    find_port(dt_socket, &port1, &port2);
    listen(dt_socket, 1);
    server->clients[id].dt_socket = dt_socket;
    server->clients[id].dt_port = port1 * 256 + port2;
    dprintf(client, "227 Entering Passive Mode (127,0,0,1,%d,%d).\r\n",
        port1, port2);
}

void user_pasv(server_t *server, int client, int id)
{
    if (server->clients[id].log == true && server->clients[id].pass == true) {
        server->clients[id].mod = PASSIVE;
        data_socket(server, client, id);
    } else {
        dprintf(client, "530 not logged in.\r\n");
    }
}
