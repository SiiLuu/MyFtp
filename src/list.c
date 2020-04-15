/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** list
*/

#include "ftp.h"

bool check_list(server_t *server, char *op, int id)
{
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    char *buf = malloc(256);

    if ((mydir = opendir(op)) != NULL) {
        dprintf(server->clients[id].fd_client,
            "150 File status okay; about to open data connection.\r\n");
        while ((myfile = readdir(mydir)) != NULL) {
            stat(buf, &mystat);
            dprintf(server->clients[id].fd_client, "%s\r\n", myfile->d_name);
        }
        return (true);
    }
    return (false);
}

void user_list(server_t *server, int client, int id)
{
    bool found = false;
    char *str = NULL;
    char *op = NULL;

    if (server->clients[id].log == true && server->clients[id].pass == true &&
        server->clients[id].mod != DISABLED) {
        op = strdup(server->clients[id].real_path);
        str = strdup(server->command);
        str[strlen(str)-2] = 0;
        strcat(op, "/");
        if (strlen(str) != 4)
            strcat(op, (str + 5));
        if (check_list(server, op, id) == true)
            found = true;
    }
    (found == false) ? (command_not_found(server, client, id)) : (0);
}
