/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** exec_commands
*/

#include "ftp.h"

void command_not_found(server_t *server, int client)
{
    dprintf(client, "TAMER\r\n");
}

void user_login(server_t *server, int client, int id)
{
    dprintf(client, "331 User name okay, need password.\r\n");
}

void user_pass(server_t *server, int client, int id)
{
    dprintf(client, "230 User logged in, proceed.\r\n");
}

void user_pwd(server_t *server, int client, int id)
{
    dprintf(client, "257 %s created.\r\n", server->clients[id].path);
}

void user_cwd(server_t *server, int client, int id)
{
    dprintf(client, "250 Requested file action okay, completed.\r\n");
}

void exec_commands(server_t *server, int client, int id)
{
    bool found = false;
    cmds_t ptr_command[5] = {{"QUIT\r\n", remove_client},
        {"USER Anonymous\r\n", user_login}, {"PASS \r\n", user_pass},
        {"PWD\r\n", user_pwd}, {"CWD\r\n", user_cwd}};

    for (int i = 0; i < 5; i++) {
        if (strcmp(ptr_command[i].command, server->command) == 0) {
            ptr_command[i].ptr(server, client, id);
            found = true;
            break;
        }
    }
    if (found == false)
        command_not_found(server, client);
}
