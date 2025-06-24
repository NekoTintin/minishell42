/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:30:38 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/24 23:02:30 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

char	**rm_whitespace_tab(char **tablo)
{
	char		**new_tab;
	int			i;
	int			j;
	int			size;

	i = -1;
	size = 0;
	while (tablo[++i])
		if (!is_whitespace(tablo[i][0]))
			size++;
	new_tab = ft_calloc(size + 1, sizeof(char *));
	if (!new_tab)
		return (NULL);
	i = -1;
	j = -1;
	while (tablo[++i])
	{
		if (!is_whitespace(tablo[i][0]))
		{
			new_tab[++j] = ft_strdup(tablo[i]);
			if (!new_tab[j])
				return (free_tab(new_tab), NULL);
		}
	}
	return (new_tab);
}

void	ft_print_errors(char *exec, int type)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(exec, 2);
	if (type == 126)
		ft_putstr_fd(": permission denied\n", 2);
	else if (type == 127)
		ft_putstr_fd(": command not found\n", 2);
	else
		perror(" ");
}

int	exec_restore_stdfd(int fd_in, int fd_out)
{
	int		code;

	code = 0;
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (ft_print_errors("dup2", 0), 1);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (ft_print_errors("dup2", 0), 1);
	close(fd_in);
	fd_in = -1;
	close(fd_out);
	fd_out = -1;
	return (code);
}

void	exec_quit(t_parser *parse, t_exec *exec)
{
	close_all_pipes(exec->pipe_tab, parse->size - 1);
	free_int_tab(exec->pipe_tab, parse->size - 1);
	if (parse)
		free_all_parser(parse);
	if (exec->env)
		ft_free_env(exec->env);
	if (exec->mini)
		free(exec->mini);
	if (exec)
		free_exec(exec);
	clear_history();
}
