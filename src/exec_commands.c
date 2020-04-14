/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** exec_commands
*/

#include "ftp.h"

void command_not_found(server_t *server, int client)
{
    (void)server;
    dprintf(client, "500 Syntax error, command unrecognized.\r\n");
}

void user_login(server_t *server, int client, int id)
{
    (void)server;
    (void)id;
    dprintf(client, "331 User name okay, need password.\r\n");
}

void user_pass(server_t *server, int client, int id)
{
    (void)server;
    (void)id;
    dprintf(client, "230 User logged in, proceed.\r\n");
}

void user_pwd(server_t *server, int client, int id)
{
    dprintf(client, "257 %s created.\r\n", server->clients[id].path);
}

void user_cdup(server_t *server, int client, int id)
{
    int i = (strlen(rindex(server->clients[id].path, '/')) - 1);
    server->clients[id].path[strlen(server->clients[id].path) - i] = 0;
    server->clients[id].real_path[strlen(server->clients[id].path) - i] = 0;
    dprintf(client, "200 Command okay.\r\n");
}

void user_pasv(server_t *server, int client, int id)
{
    (void)server;
    (void)id;
    dprintf(client, "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\r\n");
}

void user_noop(server_t *server, int client, int id)
{
    (void)server;
    (void)id;
    dprintf(client, "200 Command okay.\r\n");
}

void format(server_t *server, int id, struct dirent *myfile)
{
    if (strcmp((server->clients[id].real_path +
        (strlen(server->clients[id].real_path) - 1)), "/") != 0)
        strcat(server->clients[id].real_path, "/");
    if (strcmp((server->clients[id].path +
        (strlen(server->clients[id].path) - 1)), "/") != 0)
        strcat(server->clients[id].path, "/");
    strcat(server->clients[id].real_path, myfile->d_name);
    strcat(server->clients[id].path, myfile->d_name);
}

void user_cwd(server_t *server, int client, int id)
{
    DIR *mydir;
    struct dirent *myfile;
    struct stat mystat;
    char *buf = malloc(256);
    bool found = false;

    mydir = opendir(server->clients[id].real_path);
    while ((myfile = readdir(mydir)) != NULL) {
        stat(buf, &mystat);
        if (strncmp(myfile->d_name,
            (server->command + 4), strlen(myfile->d_name)) == 0) {
            dprintf(client, "250 Requested file action okay, completed.\r\n");
            format(server, id, myfile);            
            found = true;
            break;
        }
    }
    closedir(mydir);
    free(buf);
    (found == false) ? (command_not_found(server, client)) : (0);
}

void user_dele(server_t *server, int client, int id)
{
    (void)id;
    bool found = false;
    char *str = NULL;

    str = strdup(server->command);
    str[strlen(str)-2] = 0;
    if (remove((str + 5)) == 0) {
        dprintf(client, "250 Requested file action okay, completed.\r\n");
        found = true;
    }
    free(str);
    (found == false) ? (command_not_found(server, client)) : (0);
}

bool advanced_cmds(server_t *server, int client, int id)
{
    if (strncmp(server->command, "CWD ", 4) == 0) {
            user_cwd(server, client, id);
            return (true);
    } else if (strncmp(server->command, "DELE ", 5) == 0) {
        user_dele(server, client, id);
        return (true);
    }
    return (false);
}

void exec_commands(server_t *server, int client, int id)
{
    bool found = false;
    cmds_t ptr_command[7] = {{"QUIT\r\n", remove_client},
        {"USER Anonymous\r\n", user_login}, {"PASS \r\n", user_pass},
        {"PWD\r\n", user_pwd}, {"CDUP\r\n", user_cdup},
        {"PASV\r\n", user_pasv}, {"NOOP\r\n", user_noop}};

    for (int i = 0; i < 7; i++) {
        if (strcmp(ptr_command[i].command, server->command) == 0) {
            ptr_command[i].ptr(server, client, id);
            found = true;
            break;
        }
        if (advanced_cmds(server, client, id) == true) {
            found = true;
            break;
        }
    }
    if (found == false)
        command_not_found(server, client);
}
