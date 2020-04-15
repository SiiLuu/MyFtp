/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** commands
*/

#include "ftp.h"

void user_login(server_t *server, int client, int id)
{
    server->clients[id].log = true;
    dprintf(client, "331 User name okay, need password.\r\n");
}

void user_pass(server_t *server, int client, int id)
{
    server->clients[id].pass = true;
    dprintf(client, "230 User logged in, proceed.\r\n");
}

void user_pwd(server_t *server, int client, int id)
{
    if (server->clients[id].log == true && server->clients[id].pass == true)
        dprintf(client, "257 \"%s\" created.\r\n", server->clients[id].path);
    else
        dprintf(client, "530 not logged in.\r\n");
}

void user_noop(server_t *server, int client, int id)
{
    if (server->clients[id].log == true && server->clients[id].pass == true)
        dprintf(client, "200 Command okay.\r\n");
    else
        dprintf(client, "530 not logged in.\r\n");
}

void user_help(server_t *server, int client, int id)
{
    if (server->clients[id].log == true && server->clients[id].pass == true)
        dprintf(client, "214 Help message.\r\n");
    else
        dprintf(client, "530 not logged in.\r\n");
}