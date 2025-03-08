/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:50:51 by qupollet          #+#    #+#             */
/*   Updated: 2025/03/08 18:03:54 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_child_exec(t_cmd *cmd, pid_t pid, int *pipe, char **envp)
{
	int			return_code;

	

	if (ft_is_builtin(cmd->argument[0]) > 0)
	{
		return_code = ft_exec_buildin(cmd, envp);
		return (return_code);
	}
	else
	{
		return_code = ft_find_in_envp(&(cmd->argument[0]), envp);
		if (return_code != 0)
			return (return_code);
		
	}
	return (0);
}

int	ft_create_childs(t_parser *parser, pid_t *pid_tab, int **pipe_tab,
	char **envp)
{
	int		idx;

	idx = 0;
	while (idx < parser->size)
	{
		pid_tab[idx] = fork();
		if (pid_tab[idx] < 0)
		{
			ft_putendl_fd(
				"bash: fork failed: Resource temporarily unavailable", 2);
			pid_tab[idx] = -1;
		}
		if (pid_tab[idx] == 0)
		{
			if (ft_child_exec() < 0)
				return (-1);
		}
		idx++;
	}
	return (0);
}

int	ft_create_pipes(t_parser *parser, pid_t *pid_tab, int **pipe_tab,
	char **envp)
{
	int		idx;
	int		error;

	idx = 0;
	error = 0;
	while (idx < parser->size - 1)
	{
		if (pipe(pipe_tab[idx]) == -1)
		{
			error = 1;
			ft_putendl_fd("bash: error when creating the pipe", 2);
			continue ;
		}
		idx++;
	}
	if (ft_create_childs(parser, pid_tab, pipe_tab, envp) < 0)
	{
		ft_free_pipe(pipe_tab, idx);
		free(pid_tab);
		return (-1);
	}
	return (error);
}

int	exec_main(t_parser *parser, char **envp)
{
	pid_t		*pid_tab;
	int			**pipe_tab;
	int			status;
	int			idx;

	if (!parser || !parser->top)
		return (-1);
	pid_tab = ft_create_pid_tab(parser->size);
	if (!pid_tab)
		return (-1);
	pipe_tab = ft_create_pipe_tab(parser->size - 1);
	if (!pipe_tab)
		return (free(pid_tab), -1);
	if (ft_create_pipes(parser, pid_tab, pipe_tab, envp) == -1)
		return (-1);
	idx = -1;
	while (++idx < parser->size)
		waitpid(pid_tab[idx], &status, 0);
	return (0);
}
