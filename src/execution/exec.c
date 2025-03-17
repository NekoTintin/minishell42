/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:50:51 by qupollet          #+#    #+#             */
/*   Updated: 2025/03/17 19:06:22 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_child_exec(t_cmd *cmd, int idx, int **pipe_tab, char **envp)
{
	int			return_code;
	int			*p1;
	int			*p2;

	if (idx == 0)
		p1 = NULL;
	else
		p1 = pipe_tab[idx];
	if (cmd->next == NULL)
		p2 = NULL;
	else
		p2 = pipe_tab[idx + 1];
	return_code = ft_redirects(cmd, p1, p2);
	if (return_code != 0)
		exit (return_code);
	ft_close_pipe(p1, p2);
	return_code = ft_find_in_envp(&(cmd->argument[0]), envp);
	if (return_code != 0)
		exit (return_code);
	execve(cmd->argument[0], cmd->argument, envp);
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
		{
			if (ft_child_exec(cmd, idx, pipe_tab, envp) < 0)
				exit(1);
		}
		cmd = cmd->next;
		idx++;
	}
	return (0);
}

int	exec_loop(t_parser *parser, pid_t *pid_tab, int **pipe_tab, char **envp)
{
	t_cmd	*cmd;
	int		idx_pipe;
	int		error;

	// Redirects here TODO
	cmd = parser->top;
	idx_pipe = 0;
	while (cmd)
	{
		if (ft_is_builtin(cmd->argument[0]))
			error = ft_exec_builtin(cmd, envp);
		else
		{
			pid_tab[idx_pipe] = fork();
			if (pid_tab[idx_pipe] < 0)
				perror(ERR_FORK);
			if (pid_tab[idx_pipe] == 0)
				error = ft_child_exec(cmd, 0, pipe_tab, envp);
		}
		cmd = cmd->next;
	}
	return (error);
}

int	exec_main(t_parser *parser, char **envp)
{
	//pid_t		*pid_tab;
	//int			**pipe_tab;
	//int			status;
	//int			idx;

	if (!parser || !parser->top || !parser->top->argument[0])
		return (1);
	if (parser->size == 1)
		return (ft_case_one(parser, envp));
	return (1);
	/*pid_tab = ft_create_pid_tab(ft_builtin_counter(parser));
	if (!pid_tab)
		return (1);
	pipe_tab = ft_create_pipe_tab(ft_buildin_counter(parser));
	if (!pipe_tab)
		return (free(pid_tab), 1);
	
	idx = -1;
	while (++idx < parser->size)
		waitpid(pid_tab[idx], &status, 0);
	return (WEXITSTATUS(status));*/
}
