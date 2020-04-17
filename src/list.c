/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** list
*/

#include "ftp.h"

void check_list(int client, char *op)
{
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    char *buf = malloc(256);

    if ((mydir = opendir(op)) != NULL) {
        dprintf(client,
            "150 File status okay; about to open data connection.\r\n");
        while ((myfile = readdir(mydir)) != NULL) {
            stat(buf, &mystat);
            dprintf(client, "%s\r\n", myfile->d_name);
        }
        return;
    } else
        dprintf(client, "550 file not found.\r\n");
}

void user_list(server_t *server, int client, int id)
{
    char *str = NULL;
    char *op = NULL;

    if (server->clients[id].log == true && server->clients[id].pass == true) {
        if (server->clients[id].mod != DISABLED) {
            op = strdup(server->clients[id].real_path);
            str = strdup(server->command);
            str[strlen(str)-2] = 0;
            strcat(op, "/");
            (strlen(str) != 4) ? strcat(op, (str + 5)) : (0);
            check_list(client, op);
        } else
            dprintf(client, "425 Use PORT or PASV first.\r\n");
    } else
        dprintf(client, "530 not logged in.\r\n");
}
