/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** dele
*/

#include "ftp.h"

bool check_file(int client, char *str, char *op)
{
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    char *buf = malloc(256);

    mydir = opendir(op);
    while ((myfile = readdir(mydir)) != NULL) {
        stat(buf, &mystat);
        if (strcmp(myfile->d_name, str) == 0) {
            strcat(op, "/");
            strcat(op, str);
            remove(op);
            dprintf(client, "250 Requested file action okay, completed.\r\n");
            closedir(mydir);
            free(buf);
            return (true);
        }
    }
    closedir(mydir);
    free(buf);
    return (false);
}

void user_dele(server_t *server, int client, int id)
{
    bool found = false;
    char *str = NULL;
    char *op = NULL;

    if (server->clients[id].log == true && server->clients[id].pass == true) {
        op = strdup(server->clients[id].real_path);
        str = strdup(server->command);
        str[strlen(str)-2] = 0;
        strcat(op, "/");
        strcat(op, (str + 5));
        op[strlen(op) - (strlen(rindex(op, '/')))] = 0;
        if (strchr(str, '/') == NULL)
            str = (rindex(str, ' ') + 1);
        else
            str = (rindex(str, '/') + 1);
        if (check_file(client, str, op) == true)
            found = true;
    }
    (found == false) ? (command_not_found(server, client, id)) : (0);
}
