/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** error
*/

#include "ftp.h"

void help()
{
    puts("USAGE: ./myftp port path");
    puts("       port  is the port number on wich the server socket listens");
    puts("       path  is the path to the home directory for the Anonymous user");
    exit(0);
}

void error_handling(int ac, char **av)
{
    if (ac != 3) {
        perror("Arguments error");
        exit(84);
    } else if (atoi(av[1]) == 0) {
        perror("Port unknown");
        exit(84);
    } else if (chdir(av[2]) != 0) {
        perror("chdir");
        exit(84);
    }
}