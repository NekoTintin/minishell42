/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:50:51 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/27 02:25:01 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_child_exec(int *fd, t_cmd *cmd, char **envp)
{
	int			infile;
	int			outfile;

	return (0);
}

int	ft_create_childs(t_parser *parser, pid_t *pid_tab, int **pipe_tab)
{
	int		idx;

	idx = 0;
	while (idx < parser->size - 1)
	{
		if (pipe(pipe_tab[idx]) == -1)
		{
			ft_free_pipe(pipe_tab, idx);
			free(pid_tab);
			return (-1);
		}
	}
	idx = 0;
	while (idx < parser->size)
	{
		pid_tab[idx] = fork();
		if (pid_tab[idx] < 0)
			return (-1);
		if (pid_tab[idx] == 0)
		{
			if (ft_child_exec() < 0)
				return (-1);
		}
	}
	return (0);
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
	pipe_tab = ft_create_pipe_tab(parser->size);
	if (!pipe_tab)
		return (free(pid_tab), -1);
	if (ft_create_childs(parser, pid_tab, pipe_tab) == -1)
		return (-1);
	idx = -1;
	while (++idx < parser->size)
		waitpid(pid_tab[idx], &status, 0);
	return (0);
}
