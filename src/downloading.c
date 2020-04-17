/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** upload
*/

#include "ftp.h"

void check_path_file(int client, char *str)
{
    int filedesc = open(str, O_RDONLY);

    if (filedesc < 0) {
        dprintf(client, "550 file not found.\r\n");
        return;
    }
    dprintf(client,
        "150 File status okay; about to open data connection.\r\n");
}

void user_retr(server_t *server, int client, int id)
{
    char *str = NULL;
    char *op = NULL;

    if (server->clients[id].log == true && server->clients[id].pass == true) {
        if (server->clients[id].mod != DISABLED) {
            op = strdup(server->clients[id].real_path);
            str = strdup(server->command);
            str[strlen(str) - 2] = 0;
            strcat(op, "/");
            strcat(op, (str + 5));
            check_path_file(client, op);
        }
        else {
            dprintf(client, "425 Use PORT or PASV first.\r\n");
        }
    } else
        dprintf(client, "530 not logged in.\r\n");
}
