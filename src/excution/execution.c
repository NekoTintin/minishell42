/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:37:24 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/20 20:05:15 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/testeur.h"

static int execut_command(t_cmd *cmd);
static int execut_builtin(t_cmd *cmd);
static int execut_external(t_cmd *cmd);
static int execut_setup_redirections(t_cmd *cmd);

int mi_execution(t_parser *parser)
{
    t_cmd *c_cmd;

    if(parser == NULL || parser->top == NULL)
        return (1);
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
    if (!cmd->args || !cmd->args[0])
        return (1);
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

    if (!execut_setup_redirections(cmd) != 0)
        return (1);
    pid = fork();// Créer un nouveau processus pour exécuter la commande
    if (pid == -1)
        return(perror("forck failed"), 1);
    if (pid == 0)
    {
        execvp(cmd->args[0], cmd->args);//execve(const char *pathname, char *const argv[], char *const envp[])
        return(perror(cmd->args[0]), 1);//display error
    }
    else
        waitpid(pid, NULL, 0);// Dans le processus parent
    return(0);
}

static int execut_setup_redirections(t_cmd *cmd)
{
    int     fd;
    
    if (cmd->infile != NULL)
    {
        fd = open(cmd->infile, O_RDONLY);
        if(fd == -1)
            return (perror("open infile failed"), 1);
        dup2(fd, STDIN_FILENO);
        close (fd);
    }
    else if (cmd->outfile != NULL)
    {
        if (cmd->append)
            fd = open(cmd->outfile, O_WRONLY | O_APPEND | O_CREAT);
        else
            fd = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT);
        if(fd == -1)
            return (perror("open outfile failed"), 1);
        dup2(fd, STDOUT_FILENO);
        close (fd);
    }
    return (0);
}