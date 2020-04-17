/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cwd
*/

#include "ftp.h"

void user_cdup(server_t *server, int client, int id)
{
    int i = 0;

    if (server->clients[id].log == true && server->clients[id].pass == true) {
        i = (strlen(rindex(server->clients[id].path, '/')) - 1);
        server->clients[id].path[strlen(server->clients[id].path) - i] = 0;
        server->clients[id].real_path[strlen(
            server->clients[id].real_path) - i] = 0;
        if (strlen(server->clients[id].path) != 1) {
            server->clients[id].path[strlen(server->clients[id].path) - 1] = 0;
            server->clients[id].real_path[strlen(
                server->clients[id].real_path) - 1] = 0;
        }
        dprintf(client, "200 Command okay.\r\n");
    }
    else {
        dprintf(client, "530 not logged in.\r\n");
    }
}

void check_cwd(server_t *server, int id, char *str, int i)
{
    if (strcmp((str + 4), "..") != 0) {
        if (strcmp((server->clients[id].real_path +
            (strlen(server->clients[id].real_path) - 1)), "/") != 0)
            strcat(server->clients[id].real_path, "/");
        if (strcmp((server->clients[id].path +
            (strlen(server->clients[id].path) - 1)), "/") != 0)
            strcat(server->clients[id].path, "/");
        strcat(server->clients[id].path, (str + 4));
        strcat(server->clients[id].real_path, (str + 4));
    } else {
        i = (strlen(rindex(server->clients[id].path, '/')) - 1);
        server->clients[id].path[strlen(server->clients[id].path) - i] = 0;
        server->clients[id].real_path[strlen(
            server->clients[id].real_path) - i] = 0;
        if (strlen(server->clients[id].path) != 1) {
            server->clients[id].path[strlen(server->clients[id].path) - 1] = 0;
            server->clients[id].real_path[strlen(
                server->clients[id].real_path) - 1] = 0;
        }
    }
}

void user_cwd(server_t *server, int client, int id)
{
    DIR *mydir;
    char *str = NULL;
    char *op = NULL;
    int i = 0;

    if (server->clients[id].log == true && server->clients[id].pass == true) {
        op = strdup(server->clients[id].real_path);
        str = strdup(server->command);
        str[strlen(str)-2] = 0;
        strcat(op, "/");
        strcat(op, (str + 4));
        if ((mydir = opendir(op)) != NULL) {
            dprintf(client,
                "250 Requested file action okay, completed.\r\n");
            check_cwd(server, id, str, i);
        } else
            dprintf(client, "550 file not found.\r\n");
        closedir(mydir);
    } else
        dprintf(client, "530 not logged in.\r\n");
}
