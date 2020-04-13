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

void exec_commands(server_t *server, int client, int id)
{
    bool found = false;
    cmds_t ptr_command[1] = {{"QUIT\r\n", remove_client}};

    for (int i = 0; i < 1; i++) {
        if (strcmp(ptr_command[i].command, server->command) == 0) {
            ptr_command[i].ptr(server, client, id);
            found = true;
            break;
        }
    }
    if (found == false)
        command_not_found(server, client);
}
