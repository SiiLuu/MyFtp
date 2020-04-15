/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** active_mode
*/

#include "ftp.h"

void user_port(server_t *server, int client, int id)
{
    if (server->clients[id].log == true && server->clients[id].pass == true) {
        server->clients[id].mod = ACTIVE;
        dprintf(client, "200 Command okay.\r\n");
    } else {
        dprintf(client, "530 not logged in.\r\n");
    }
}
