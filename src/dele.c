/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** dele
*/

#include "ftp.h"

void user_dele(server_t *server, int client, int id)
{
    (void)id;
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    char *buf = malloc(256);
    bool found = false;
    char *str = NULL;
    char *op = NULL;
    int i = 0;

    op = strdup(server->clients[id].real_path);
    str = strdup(server->command);
    str[strlen(str)-2] = 0;
    strcat(op, "/");
    strcat(op, (str + 5));
    i = (strlen(rindex(op, '/')));
    op[strlen(op) - i] = 0;
    if (strlen(op) == 1)
        str = (rindex(str, ' ') + 1);
    else
        str = (rindex(str, '/') + 1);
    mydir = opendir(op);
    while ((myfile = readdir(mydir)) != NULL) {
        stat(buf, &mystat);
        if (strcmp(myfile->d_name, str) == 0) {
            strcat(op, "/");
            strcat(op, str);
            remove(op);
            dprintf(client, "250 Requested file action okay, completed.\r\n");
            found = true;
            break;
        }
    }
    closedir(mydir);
    free(buf);
    (found == false) ? (command_not_found(server, client)) : (0);
}
