/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 02:25:00 by qupollet          #+#    #+#             */
/*   Updated: 2025/03/16 00:16:41 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			ft_freetab(char **args);
void			ft_free_pipe(int **pipe, int tab_size);

int	ft_builtin_counter(t_parser *parser)
{
	t_cmd	*cur;
	int		counter;

	cur = parser->top;
	counter = 0;
	while (cur)
	{
		if (ft_is_builtin(cur->argument[0]))
			counter++;
		cur = cur->next;
	}
	return (counter);
}

pid_t	*ft_create_pid_tab(int table_size)
{
	pid_t	*pid_tab;

	pid_tab = ft_calloc(table_size, sizeof(pid_t));
	if (!pid_tab)
		return (NULL);
	return (pid_tab);
}

int	**ft_create_pipe_tab(int table_size)
{
	int		**pipe_tab;
	int		idx;

	pipe_tab = ft_calloc((table_size - 1), sizeof(int *));
	if (!pipe_tab)
		return (NULL);
	idx = 0;
	while (idx < table_size - 1)
	{
		pipe_tab[idx] = ft_calloc(2, sizeof(int));
		if (!pipe_tab[idx])
			return (ft_free_pipe(pipe_tab, idx), NULL);
		if (pipe(pipe_tab[idx]) == -1)
		{
			ft_putendl_fd("bash: error when creating the pipe", 2);
			free(pipe_tab[idx]);
			pipe_tab[idx] = NULL;
		}
		idx++;
	}
	return (pipe_tab);
}

void	ft_free_pipe(int **pipe_tab, int tab_size)
{
	int		idx;

	idx = -1;
	while (++idx < tab_size - 1)
		free(pipe_tab[idx]);
	free(pipe_tab);
}

void	ft_freetab(char **args)
{
	int	idx;

	idx = -1;
	while (args[++idx] != NULL)
		free(args[idx]);
	free(args);
}
