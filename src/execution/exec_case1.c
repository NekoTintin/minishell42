/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_case1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:10:31 by qupollet          #+#    #+#             */
/*   Updated: 2025/04/04 15:52:59 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_case1_child(t_cmd *cmd, char**envp)
{
	pid_t	child;
	int		status;
	int		error;

	child = fork();
	if (child < 0)
		return (ft_putendl_fd("bash: fork", 2), 1);
	else if (child == 0)
	{
		error = ft_find_in_envp(&(cmd->argument[0]), envp);
		if (error != 0)
			exit (error);
		error = ft_checkprog(cmd->argument[0]);
		if (error != 0)
			exit (error);
		if (execve(cmd->argument[0], cmd->argument, envp) == -1)
		{
			ft_print_errors(cmd->argument[0]);
			exit (1);
		}
	}
	waitpid(child, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	ft_case_one(t_parser *parser, char **envp)
{
	t_cmd	*cmd;
	int		is_builtin;

	cmd = parser->top;
	if (ft_redirects(cmd, NULL, NULL) == 1)
		return (1);
	is_builtin = ft_is_builtin(cmd->argument[0]);
	if (is_builtin >= 1)
		return (ft_exec_builtin(cmd, envp));
	else
		return (exec_case1_child(cmd, envp));
}
