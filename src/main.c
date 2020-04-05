/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** main
*/

#include "ftp.h"

int main(int ac, char **av)
{
    if (strcmp(av[1], "-h") || strcmp(av[1], "-help"))
        help();
    error_handling(ac, av);
    return (0);
}