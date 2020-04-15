/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** exec_commands
*/

#include "ftp.h"

void command_not_found(server_t *server, int client, int id)
{
    if (strncmp(server->command, "USER ", 5) == 0)
        dprintf(client, "331 bad user.\r\n");
    else if (server->clients[id].log == true &&
        server->clients[id].pass == true)
        dprintf(client, "500 Syntax error, command unrecognized.\r\n");
    else
        dprintf(client, "530 not logged in.\r\n");
}

bool advanced_cmds(server_t *server, int client, int id)
{
    if (strncmp(server->command, "CWD ", 4) == 0) {
        user_cwd(server, client, id);
        return (true);
    }
    if (strncmp(server->command, "DELE ", 5) == 0) {
        user_dele(server, client, id);
        return (true);
    }
    if (strncmp(server->command, "LIST", 4) == 0) {
        user_list(server, client, id);
        return (true);
    }
    return (false);
}

void user_help(server_t *server, int client, int id)
{
    if (server->clients[id].log == true && server->clients[id].pass == true)
        dprintf(client, "214 Help message.\r\n");
    else
        dprintf(client, "530 not logged in.\r\n");
}

void exec_commands(server_t *server, int client, int id)
{
    bool found = false;
    cmds_t ptr_command[8] = {{"QUIT\r\n", remove_client},
        {"USER Anonymous\r\n", user_login}, {"PASS \r\n", user_pass},
        {"PWD\r\n", user_pwd}, {"CDUP\r\n", user_cdup},
        {"PASV\r\n", user_pasv}, {"NOOP\r\n", user_noop},
        {"HELP\r\n", user_help}};

    for (int i = 0; i < 8; i++) {
        if (strcmp(ptr_command[i].command, server->command) == 0) {
            ptr_command[i].ptr(server, client, id);
            found = true;
            break;
        } else if (advanced_cmds(server, client, id) == true) {
            found = true;
            break;
        }
    }
    (found == false) ? command_not_found(server, client, id) : (0);
}
