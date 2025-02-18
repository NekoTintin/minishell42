/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:37:24 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/18 18:00:23 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../../includes/minishell.h"

static int execut_command(t_cmd *cmd);
static int execut_builtin(t_cmd *cmd);
static int execut_external(t_cmd *cmd);
static int execut_setup_redirections(infile, outfile, append);

int mi_execution(t_parser *parser)
{
    t_cmd *c_cmd;

    if(parser == NULL)
        return (0);
    c_cmd = parser->top;
    while (c_cmd != NULL)
    {
        execut_command(c_cmd);
        c_cmd = c_cmd->next;
    }
    return (0);// <-TO DO fonction free parser.
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
    // !! comportement indefini si la cmd existe pas !!
    if (!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])))
        printf("cd\n");
    else if (!ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])))
        printf("exit\n");
    else if (!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])))
        printf("export\n");
    else if (!ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])))
        printf("unset\n");
    else if (!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])))
        printf("env\n");
    return (0);
}

static int execut_external(t_cmd *cmd)
{
    pid_t pid;
    // Préparer les redirections
    setup_redirections(cmd->infile, cmd->outfile, cmd->append);

    // Créer un nouveau processus pour exécuter la commande
    pid = fork();

    if (pid == 0)
    {
        // Dans le processus enfant
        execvp(cmd->args[0], cmd->args);//execve(const char *pathname, char *const argv[], char *const envp[])
        // Si execvp échoue
        perror("Execution failed");
        exit(EXIT_FAILURE);
    }
    else
        waitpid(pid, NULL, 0);// Dans le processus parent
    return(0);
}

static int execut_setup_redirections(t_cmd *cmd)
{
    if (cmd->infile != NULL)
    {
        // Rediriger lentrée standard
        open(cmd->infile, O_RDONLY);
        dup2("file_descriptor", STDIN_FILENO);
    }
    else if (cmd->outfile != NULL)
    {
        // Rediriger la sortie standard
        if (cmd->append)//Veriefier la condition 
            open(cmd->outfile, O_WRONLY | O_APPEND | O_CREAT);
        else
            open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT);
        dup2('file_descriptor', STDOUT_FILENO);
    }
}