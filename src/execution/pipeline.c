/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:33:00 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/29 15:28:44 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipeline_free(t_pipeline *top)
{
	t_pipeline	*cur;
	t_pipeline	*next;

	cur = top;
	while (cur)
	{
		next = cur->next;
		if (cur->pipe_in != -1)
		{
			close(cur->pipe_in);
			cur->pipe_in = -1;
		}
		if (cur->pipe_out != -1)
		{
			close(cur->pipe_out);
			cur->pipe_out = -1;
		}
		free(cur);
		cur = next;
	}
}

int	**create_tab_pipe(int nb_child)
{
	int	**pipe_tab;
	int	idx;

	pipe_tab = ft_calloc(nb_child - 1, sizeof(int *));
	if (!pipe_tab)
		return (NULL);
	idx = 0;
	while (idx < nb_child - 1)
	{
		pipe_tab[idx] = ft_calloc(2, sizeof(int));
		if (!pipe_tab[idx])
			return (free_int_tab(pipe_tab, idx), NULL);
		if (pipe(pipe_tab[idx]) == -1)
			return (free_int_tab(pipe_tab, idx), NULL);
		idx++;
	}
	return (pipe_tab);
}

int	ft_create_pipes(t_pipeline *top, int nb_child)
{
	t_pipeline	*cur;
	int			**pipe_tab;
	int			idx;

	pipe_tab = create_tab_pipe(nb_child);
	if (!pipe_tab)
		return (1);
	cur = top;
	idx = 0;
	while (cur)
	{
		if (idx == 0)
			cur->pipe_in = STDIN_FILENO;
		else
			cur->pipe_in = pipe_tab[idx - 1][0];
		if (idx == nb_child - 1)
			cur->pipe_out = STDOUT_FILENO;
		else
			cur->pipe_out = pipe_tab[idx][1];
		cur = cur->next;
		idx++;
	}
	free_int_tab(pipe_tab, nb_child - 1);
	return (0);
}

t_pipeline	*pipeline_init(int nb, t_cmd *cmd)
{
	t_pipeline	*top;
	t_pipeline	*cur;
	t_cmd		*tmp_cmd;

	top = ft_calloc(1, sizeof(t_pipeline));
	if (!top)
		return (NULL);
	cur = top;
	cur->cmd = cmd;
	tmp_cmd = cmd->next;
	while (nb > 0)
	{
		cur->pid = -1;
		cur->next = ft_calloc(1, sizeof(t_pipeline));
		if (!cur->next)
			return (NULL);
		cur->cmd = tmp_cmd;
		tmp_cmd = tmp_cmd->next;
		cur = cur->next;
		nb--;
	}
	return (top);
}

t_pipeline	*ft_create_pipeline(int nb, t_cmd *cmd)
{
	t_pipeline	*top;

	if (nb <= 0 || !cmd)
		return (NULL);
	top = pipeline_init(nb, cmd);
	if (!top)
		return (pipeline_free(top), NULL);
	if (ft_create_pipes(top) == 1)
		return (pipeline_free(top), NULL);
	return (top);
}
