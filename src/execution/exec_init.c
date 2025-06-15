/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:19:22 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/04 02:46:23 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_int_tab(int **tablo, int size)
{
	int	idx;

	if (!tablo)
		return ;
	idx = 0;
	while (idx < size)
	{
		free(tablo[idx]);
		tablo[idx] = NULL;
		idx++;
	}
	free(tablo);
	tablo = NULL;
}

int	close_all_pipes(int **tablo, int size)
{
	int			idx;
	int			error;

	if (!tablo)
		return (1);
	idx = 0;
	error = 0;
	while (idx < size)
	{
		if (tablo[idx] && tablo[idx][0] >= 0)
			if (close(tablo[idx][0]) == -1)
				error = 1;
		if (tablo[idx] && tablo[idx][1] >= 0)
			if (close(tablo[idx][1]) == -1)
				error = 1;
		idx++;
	}
	if (error)
		ft_print_errors("close", 0);
	return (error);
}

int	create_pipes(int **tablo, int size)
{
	int		idx;

	idx = 0;
	while (idx < size)
	{
		if (pipe(tablo[idx]) == -1)
		{
			close_all_pipes(tablo, idx);
			ft_print_errors("pipe", 0);
			return (1);
		}
		idx++;
	}
	return (0);
}

int	**pipe_tab_init(int size)
{
	int		**tablo;
	int		idx;

	tablo = ft_calloc(size, sizeof(int *));
	if (!tablo)
		return (NULL);
	idx = 0;
	while (idx < size)
	{
		tablo[idx] = ft_calloc(2, sizeof(int));
		if (!tablo[idx])
			return (free_int_tab(tablo, idx), NULL);
		idx++;
	}
	return (tablo);
}

t_exec	*exec_init(int child, t_cmd *top, t_env *env)
{
	t_exec		*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->nb_child = child;
	exec->env = env;
	exec->top = ft_create_pipeline(child, top, exec);
	if (!exec->top)
		return (free(exec), NULL);
	exec->pipe_tab = pipe_tab_init(child - 1);
	if (!exec->pipe_tab)
		return (pipeline_free(exec->top), free(exec), NULL);
	if (create_pipes(exec->pipe_tab, child - 1) != 0)
	{
		pipeline_free(exec->top);
		free_int_tab(exec->pipe_tab, child - 1);
		free(exec);
		return (NULL);
	}
	return (exec);
}
