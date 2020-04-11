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

void init_struct_sockaddr(struct sockaddr_in *name, int port)
{
    name->sin_addr.s_addr = inet_addr("127.0.0.1");
    name->sin_port = htons(port);
    name->sin_family = AF_INET;
}

int create_client_socket()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket");
        exit(84);
    }
    return (sock);
}

void main_loop(int sock, struct sockaddr_in name)
{
    int server_sock = 0;
    socklen_t size = sizeof(name);
    char *str = malloc(256);
 
    server_sock = connect(sock, (struct sockaddr *)&name, size);
    if (server_sock == -1) {
        perror("Connect");
        exit(84);
    }
    dprintf(sock, "Hello world\n");
    read(sock, str, 256);
    printf("Server said: %s", str);
    close(server_sock);
    close(sock);
}

int main(int argc, char **argv)
{
    int sock = 0;
    struct sockaddr_in name;
    int port = atoi(argv[2]);
   
    sock = create_client_socket();
    init_struct_sockaddr(&name, port);
    main_loop(sock, name);
    return (0);
}
