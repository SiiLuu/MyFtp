/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** dele
*/

#include "ftp.h"

void check_file(int client, char *str)
{
    int filedesc = open(str, O_RDONLY);

    if (filedesc < 0) {
        dprintf(client, "550 file not found.\r\n");
        return;
    }
    if ((remove(str)) == -1) {
        dprintf(client, "550 file not found.\r\n");
        return;
    }
    dprintf(client, "250 Requested file action okay, completed.\r\n");
}

void user_dele(server_t *server, int client, int id)
{
    char *str = NULL;
    char *op = NULL;

    if (server->clients[id].log == true && server->clients[id].pass == true) {
        op = strdup(server->clients[id].real_path);
        str = strdup(server->command);
        str[strlen(str)-2] = 0;
        strcat(op, "/");
        strcat(op, (str + 5));
        check_file(client, op);
    } else
        dprintf(client, "530 not logged in.\r\n");
}
