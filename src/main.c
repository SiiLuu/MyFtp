/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** main
*/

#include "ftp.h"

int main(int ac, char **av)
{
    server_t *server = malloc(sizeof(server_t));
    server->clients = malloc(sizeof(clients_t));

    if (!strcmp(av[1], "-h") || !strcmp(av[1], "-help"))
        help();
    error_handling(ac, av);
    server->port = atoi(av[1]);
    server->path = av[2];
    start_server(server);
    return (0);
}
