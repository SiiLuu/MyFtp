/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** commands
*/

#include "ftp.h"

void user_login(server_t *server, int client, int id)
{
    (void)server;
    (void)id;
    dprintf(client, "331 User name okay, need password.\r\n");
}

void user_pass(server_t *server, int client, int id)
{
    (void)server;
    (void)id;
    dprintf(client, "230 User logged in, proceed.\r\n");
}

void user_pwd(server_t *server, int client, int id)
{
    dprintf(client, "257 %s created.\r\n", server->clients[id].path);
}

void user_pasv(server_t *server, int client, int id)
{
    (void)server;
    (void)id;
    dprintf(client, "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\r\n");
}

void user_noop(server_t *server, int client, int id)
{
    (void)server;
    (void)id;
    dprintf(client, "200 Command okay.\r\n");
}
