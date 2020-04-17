/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** dele
*/

#include "ftp.h"

bool check_file(int client, char *str)
{
    int filedesc = open(str, O_RDONLY);

    if(filedesc < 0)
        return (false);
    if ((remove(str)) == -1)
        return (false);
    dprintf(client, "250 Requested file action okay, completed.\r\n");
    return (true);
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
        if (check_file(client, op) == true)
            found = true;
    }
    (found == false) ? (command_not_found(server, client, id)) : (0);
}
