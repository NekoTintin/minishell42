/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:33:00 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/28 19:24:40 by qupollet         ###   ########.fr       */
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
		if (cur->pipe_in[0] != -1)
			close(cur->pipe_in[0]);
		if (cur->pipe_in[1] != -1)
			close(cur->pipe_in[1]);
		if (cur->pipe_out[0] != -1)
			close(cur->pipe_out[0]);
		if (cur->pipe_out[1] != -1)
			close(cur->pipe_out[1]);
		free(cur);
		cur = next;
	}
}

int	init_pipe_to_null(int pipe[2])
{
	pipe[0] = -1;
	pipe[1] = -1;
	return (0);
}

int	ft_create_pipes(t_pipeline *top)
{
	t_pipeline	*cur;

	cur = top;
	while (cur)
	{
		if (cur != top)
		{
			if (pipe(cur->pipe_in) == -1)
				return (1);
		}
		else
			init_pipe_to_null(cur->pipe_in);
		if (cur->next)
		{
			if (pipe(cur->pipe_out) == -1)
				return (1);
		}
		else
			init_pipe_to_null(cur->pipe_out);
		cur = cur->next;
	}
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
