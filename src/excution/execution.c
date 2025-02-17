/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:37:24 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/17 16:52:28 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../../includes/minishell.h"

int mi_execution(t_parser *parser);
static int execut_command(t_cmd *cmd);
static int execut_builtin(t_cmd *cmd);
static int execut_external(t_cmd *cmd);

int mi_execution(t_parser *parser)
{
    t_cmd *curr_cmd;

    curr_cmd = parser->top;
    while (curr_cmd->next != NULL)
    {
        execut_command(curr_cmd);
        curr_cmd = curr_cmd->next;
    }
    return (0);
}

static int execut_command(t_cmd *cmd)
{
    if(cmd->is_builtin)
        execut_builtin(cmd);
    else
        execut_external(cmd);
    return (0);
}

static int execut_builtin(t_cmd *cmd)
{
    if (cmd->args[0] == "cd")
        printf("cd\n");
    else if (cmd->args[0] == "exit")
        printf("exit");
    else if (cmd->args[0] == "export")
        printf("export");
    else if (cmd->args[0] == "unset")
        printf("unset");
    else if (cmd->args[0] == "env")
        printf("env");
    return (0);
}

static int execut_external(t_cmd *cmd)
{
    return(0);
}
/*
//======================================================

function execute_external(cmd: t_cmd):
    # Préparer les redirections
    setup_redirections(cmd.infile, cmd.outfile, cmd.append)

    # Créer un nouveau processus pour exécuter la commande
    pid = fork()

    if pid == 0:
        # Dans le processus enfant
        execvp(cmd.args[0], cmd.args)
        # Si execvp échoue
        perror("Execution failed")
        exit(EXIT_FAILURE)
    else:
        # Dans le processus parent
        waitpid(pid, null, 0)

//======================================================

function setup_redirections(infile, outfile, append):
    if infile is not null:
        # Rediriger lentrée standard
        open(infile, O_RDONLY)
        dup2(file_descriptor, STDIN_FILENO)

    if outfile is not null:
        # Rediriger la sortie standard
        if append:
            open(outfile, O_WRONLY | O_APPEND | O_CREAT)
        else:
            open(outfile, O_WRONLY | O_TRUNC | O_CREAT)
        dup2(file_descriptor, STDOUT_FILENO)

*/