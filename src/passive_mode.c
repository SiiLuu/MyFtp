/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** passive_mode
*/

#include "ftp.h"

void user_pasv(server_t *server, int client, int id)
{
    if (server->clients[id].log == true && server->clients[id].pass == true) {
        server->clients[id].mod = PASSIVE;
        dprintf(client, "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\r\n");
    } else {
        dprintf(client, "530 not logged in.\r\n");
    }
}