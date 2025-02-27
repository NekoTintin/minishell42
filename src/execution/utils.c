/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 02:25:00 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/24 03:19:08 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void			ft_freetab(char **args);
void			ft_free_pipe(int **pipe, int tab_size);

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

	pipe_tab = ft_calloc(table_size, sizeof(int *));
	if (!pipe_tab)
		return (NULL);
	idx = 0;
	while (idx < table_size)
	{
		pipe_tab[idx] = ft_calloc(2, sizeof(int));
		if (!pipe_tab[idx])
			return (ft_free_pipe(pipe_tab, idx), NULL);
		idx++;
	}
	return (pipe_tab);
}

void	ft_free_pipe(int **pipe_tab, int tab_size)
{
	int		idx;

	idx = -1;
	while (pipe_tab[++idx] < tab_size - 1)
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
