/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** upload
*/

#include "ftp.h"

void check_path(int client, char *str)
{
    int filedesc = open(str, O_RDONLY);

    if(filedesc < 0) {
        dprintf(client, "500 Syntax error.\r\n");
        return;
    }
    dprintf(client,
        "150 File status okay; about to open data connection.\r\n");
}

void user_stor(server_t *server, int client, int id)
{
    char *str = NULL;
    char *op = NULL;

    if (server->clients[id].log == true && server->clients[id].pass == true &&
        server->clients[id].mod != DISABLED) {
        op = strdup(server->clients[id].real_path);
        str = strdup(server->command);
        str[strlen(str) - 2] = 0;
        strcat(op, "/");
        strcat(op, (str + 5));
        check_path(client, op);
    }
}
