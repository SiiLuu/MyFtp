/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** upload
*/

#include "ftp.h"

void upload(server_t *server, int id, int sock, char *op)
{
    FILE *f = NULL;
    int pid = 0;
    char buf[2] = {0};

    chdir(server->clients[id].real_path);
    f = fopen(op, "w+");
    if ((pid = fork()) == 0) {
        while ((read(sock, buf, 1))) {
            buf[1] = '\0';
            fwrite(buf, 1, 1, f);
        }
        dprintf(server->clients[id].fd_client, "226 Done.\r\n");
        fclose(f);
        exit(0);
    }
}

void check_path(server_t *server, int id, int client, char *op)
{
    struct sockaddr_in inf;
    socklen_t len = sizeof(inf);
    int sock = accept(server->clients[id].dt_socket,
        (struct sockaddr *)&inf, &len);

    dprintf(client,
        "150 File status okay; about to open data connection.\r\n");
    upload(server, id, sock, op);
    close(sock);
    close(server->clients[id].dt_socket);
    server->clients[id].mod = DISABLED;
}

void user_stor(server_t *server, int client, int id)
{
    char *str = NULL;
    char *op = NULL;

    if (server->clients[id].log == true && server->clients[id].pass == true &&
        server->clients[id].mod != DISABLED) {
        op = strdup(server->clients[id].real_path);
        str = strdup(server->command);
        str[strlen(str) - 2] = 0;
        strcat(op, "/");
        strcat(op, (str + 5));
        check_path(server, id, client, op);
    } else
        dprintf(client, "530 not logged in.\r\n");
}
