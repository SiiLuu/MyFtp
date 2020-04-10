/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** client
*/

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
#include <sys/time.h>
#include <sys/types.h>

int create_tcp_socket(int port)
{
	int opt = 1;
	int fd_sock = 0;
	struct sockaddr_in sin;
	socklen_t len = sizeof(sin);

	fd_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (setsockopt(fd_sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
        &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	bind(fd_sock, (struct sockaddr*)&sin, len);
	listen(fd_sock, 10);
	return (fd_sock);
}

void main_loop(int fd_serve)
{
    fd_set set_read;
    fd_set set_write;
	int fd_client = 0;
	struct sockaddr_in cin;
	socklen_t len_cin = sizeof(cin);
	char *str = malloc(256);

    FD_ZERO(&set_read);
    FD_ZERO(&set_write);
	FD_SET(fd_serve, &set_read);

    while ((select(fd_serve + 1, &set_read, &set_write, NULL, NULL) != -1)) {
		if (FD_ISSET(fd_serve, &set_read)) {
	        fd_client = accept(fd_serve, (struct sockaddr*)&cin, &len_cin);
	        dprintf(fd_client, "Hello world\n");
			read(fd_client, str, 256);
			printf("Client said : %s", str);
	        close(fd_client);
        }
    }
}

int main(int ac, char **av)
{
	int fd_serve = 0;

	fd_serve = create_tcp_socket(atoi(av[1]));
	main_loop(fd_serve);
	close(fd_serve);
	return (0);
}
