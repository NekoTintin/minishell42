/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:50:51 by qupollet          #+#    #+#             */
/*   Updated: 2025/04/15 19:54:44 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_create_pipes(int **pipe_tab, int nb_child);

int	ft_exec_child(t_cmd *cmd, int **pipes, int cmd_idx, char **envp)
{
	int		code;
	int		*pipe1;
	int		*pipe2;

	if (cmd_idx == 0)
		pipe1 = NULL;
	else
		pipe1 = pipes[cmd_idx - 1];
	if (cmd->next == NULL)
		pipe2 = NULL;
	else
		pipe2 = pipes[cmd_idx];
	code = ft_redirects(cmd, pipe1, pipe2);
	if (code != 0)
		exit (code);
	ft_close_pipe(pipe1, 1, 1);
	ft_close_pipe(pipe2, 1, 1);
	code = ft_find_in_envp(&(cmd->argument[0]), envp);
	if (code != 0)
		exit (code);
	if (execve(cmd->argument[0], cmd->argument, envp) == -1)
		ft_print_errors(cmd->argument[0]);
	exit (1);
}

int	exec_loop(t_parser *parser, pid_t *pid_tab, int **pipe_tab, char **envp)
{
	t_cmd	*cmd;
	int		idx;
	int		error;

	error = exec_create_pipes(pipe_tab, parser->size);
	if (error != 0)
		return (error);
	cmd = parser->top;
	idx = 0;
	while (cmd)
	{
		pid_tab[idx] = fork();
		if (pid_tab[idx] < 0)
			return (perror("bash: fork"), 1);
		else if (pid_tab[idx] == 0)
		{
			error = ft_exec_child(cmd, pipe_tab, idx, envp);
			if (error != 0)
				exit (error);
		}
		cmd = cmd->next;
		idx++;
	}
	ft_close_all_pipes(pipe_tab, idx);
	return (error);
}

int	exec_create_pipes(int **pipe_tab, int nb_child)
{
	int		idx;

	if (nb_child <= 1)
		return (1);
	idx = 0;
	while (pipe_tab[idx] != NULL)
	{
		if (pipe(pipe_tab[idx]) == -1)
		{
			perror("bash: pipe");
			return (1);
		}
		idx++;
	}
	return (0);
}

int	exec_main(t_parser *parser, char **envp)
{
	pid_t		*pid_tab;
	int			**pipe_tab;
	int			status;
	int			idx;
	int			error;

	if (!parser || !parser->top || !parser->top->argument[0])
		return (1);
	if (parser->size == 1)
		return (ft_case_one(parser, envp));
	pid_tab = ft_create_pid_tab(parser->size);
	if (!pid_tab)
		return (1);
	pipe_tab = ft_create_pipe_tab(parser->size);
	if (!pipe_tab)
		return (free(pid_tab), 1);
	error = exec_loop(parser, pid_tab, pipe_tab, envp);
	if (error != 0)
		return (exec_freeall(pid_tab, pipe_tab), error);
	idx = -1;
	while (++idx < parser->size)
		waitpid(pid_tab[idx], &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}
