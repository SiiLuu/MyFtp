/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** list
*/

#include "ftp.h"

void listing(int client, int sock, char *op)
{
    int pid = 0;
    char *command = calloc(0, sizeof(256));
    int temp = 0;

    if ((pid = fork()) == 0) {
        command = strcat(command, "ls -l ");
        op ? command = strcat(command, op) : (0);
        temp = dup(1);
        dup2(sock, 1);
        system(command);
        dup2(temp, 1);
        dprintf(client, "226 Done.\r\n");
        exit(0);
    }
}

void check_list(server_t *server, int client, int id, char *op)
{
    DIR *mydir;
    struct sockaddr_in inf;
    socklen_t len = sizeof(inf);
    int sock = accept(server->clients[id].dt_socket,
        (struct sockaddr *)&inf, &len);

    if ((mydir = opendir(op)) != NULL) {
        dprintf(client,
            "150 File status okay; about to open data connection.\r\n");
        if (server->clients[id].mod == PASSIVE) {
            listing(client, sock, op);
            close(sock);
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
            check_list(server, client, id, op);
        } else
            dprintf(client, "425 Use PORT or PASV first.\r\n");
    } else
        dprintf(client, "530 not logged in.\r\n");
}
