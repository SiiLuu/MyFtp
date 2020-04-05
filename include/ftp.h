/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** ftp
*/

#ifndef FTP_H_
#define FTP_H_

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>

void help();
void error_handling(int, char**);

#endif /* !FTP_H_ */
