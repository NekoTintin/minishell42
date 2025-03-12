/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:50:51 by qupollet          #+#    #+#             */
/*   Updated: 2025/03/12 14:38:33 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_child_exec(t_cmd *cmd, int *p_input, int *p_output, char **envp)
{
	int			return_code;

	return_code = ft_redirects(cmd, p_input, p_output);
	if (return_code != 0)
		exit (return_code);
	ft_close_pipe(p_input, p_output);
	if (ft_is_builtin(cmd->argument[0]) > 0)
		exit (ft_exec_builtin(cmd, envp));
	else
	{
		return_code = ft_find_in_envp(&(cmd->argument[0]), envp);
		if (return_code != 0)
			exit (return_code);
		execve(cmd->argument[0], cmd->argument, envp);
	}
	ft_print_errors(cmd->argument[0]);
	exit (1);
}

int	ft_create_childs(t_parser *parser, pid_t *pid_tab, int **pipe_tab,
	char **envp)
{
	int		idx;
	t_cmd	*cmd;

	cmd = parser->top;
	idx = 0;
	while (cmd)
	{
		pid_tab[idx] = fork();
		if (pid_tab[idx] < 0)
		{
			ft_putendl_fd(ERR_FORK, 2);
			pid_tab[idx] = -1;
		}
		else if (pid_tab[idx] == 0)
			exit(ft_child_exec(cmd, pipe_tab[idx - 1],
					pipe_tab[idx], envp) < 0);
		cmd = cmd->next;
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
		return (1);
	pid_tab = ft_create_pid_tab(parser->size);
	if (!pid_tab)
		return (1);
	pipe_tab = ft_create_pipe_tab(parser->size - 1);
	if (!pipe_tab)
		return (free(pid_tab), 1);
	if (ft_create_pipes(parser, pid_tab, pipe_tab, envp) == -1)
		return (1);
	idx = -1;
	while (++idx < parser->size)
		waitpid(pid_tab[idx], &status, 0);
	return (WEXITSTATUS(status));
}
