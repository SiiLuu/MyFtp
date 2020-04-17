/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** upload
*/

#include "ftp.h"

void download(server_t *server, int id, int sock, int file)
{
    int pid = 0;
    int ret = 1;
    char c = 0;

    if ((pid = fork()) == 0) {
        while (ret == 1) {
            ret = read(file, &c, 1);
            if (ret == 1 && c == '\n')
                dprintf(sock, "\r\n");
            else if (ret == 1)
                dprintf(sock, &c, 1);
        }
        dprintf(server->clients[id].fd_client, "226 Done.\r\n");
        close(file);
        exit(0);
    }
}

void check_path_file(server_t *server, int id, int client, char *op)
{
    struct sockaddr_in inf;
    socklen_t len = sizeof(inf);
    int sock = accept(server->clients[id].dt_socket,
        (struct sockaddr *)&inf, &len);
    int filedesc = open(op, O_RDONLY);

    if (filedesc < 0) {
        dprintf(client, "550 file not found.\r\n");
        return;
    }
    dprintf(client,
        "150 File status okay; about to open data connection.\r\n");
    download(server, id, sock, filedesc);
    close(sock);
    close(server->clients[id].dt_socket);
    server->clients[id].mod = DISABLED;
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
            check_path_file(server, id, client, op);
        }
        else {
            dprintf(client, "425 Use PORT or PASV first.\r\n");
        }
    } else
        dprintf(client, "530 not logged in.\r\n");
}
