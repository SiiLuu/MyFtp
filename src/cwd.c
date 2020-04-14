/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** cwd
*/

#include "ftp.h"

void user_cdup(server_t *server, int client, int id)
{
    if (server->clients[id].log == true && server->clients[id].pass == true) {
        int i = (strlen(rindex(server->clients[id].path, '/')) - 1);
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

void format(server_t *server, int id, struct dirent *myfile)
{
    if (strcmp((server->clients[id].real_path +
        (strlen(server->clients[id].real_path) - 1)), "/") != 0)
        strcat(server->clients[id].real_path, "/");
    if (strcmp((server->clients[id].path +
        (strlen(server->clients[id].path) - 1)), "/") != 0)
        strcat(server->clients[id].path, "/");
    strcat(server->clients[id].real_path, myfile->d_name);
    strcat(server->clients[id].path, myfile->d_name);
}

void user_cwd(server_t *server, int client, int id)
{
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    char *buf = malloc(256);
    bool found = false;

    if (server->clients[id].log == true && server->clients[id].pass == true) {
        mydir = opendir(server->clients[id].real_path);
        while ((myfile = readdir(mydir)) != NULL) {
            stat(buf, &mystat);
            if (strncmp(myfile->d_name,
                (server->command + 4), strlen(myfile->d_name)) == 0) {
                dprintf(client, "250 Requested file action okay, completed.\r\n");
                format(server, id, myfile);
                found = true;
                break;
            }
        }
        closedir(mydir);
        free(buf);
    }
    (found == false) ? (command_not_found(server, client, id)) : (0);
}
