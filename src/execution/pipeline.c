/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 16:33:00 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/29 17:39:17 by qupollet         ###   ########.fr       */
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
		free(cur);
		cur = next;
	}
}

void	init_id(t_pipeline *top)
{
	t_pipeline	*cur;
	int			id;

	if (!top)
		return ;
	cur = top;
	id = 0;
	while (cur)
	{
		cur->id = id;
		cur = cur->next;
		id++;
	}
}

t_pipeline	*pipeline_init(int nb, t_cmd *top_cmd, t_exec *exec)
{
	t_pipeline	*top_pl;
	t_pipeline	*cur_pl;
	t_cmd		*cur_cmd;

	top_pl = ft_calloc(1, sizeof(t_pipeline));
	if (!top_pl)
		return (NULL);
	cur_pl = top_pl;
	cur_cmd = top_cmd;
	while (nb > 0)
	{
		cur_pl->cmd = cur_cmd;
		cur_pl->pid = -1;
		cur_pl->exec = exec;
		if (nb == 1)
			return (top_pl);
		cur_pl->next = ft_calloc(1, sizeof(t_pipeline));
		if (!cur_pl->next)
			return (NULL);
		cur_pl = cur_pl->next;
		cur_cmd = cur_cmd->next;
		nb--;
	}
	return (top_pl);
}

t_pipeline	*ft_create_pipeline(int nb, t_cmd *cmd, t_exec *exec)
{
	t_pipeline	*top;

	if (nb <= 0 || !cmd)
		return (NULL);
	top = pipeline_init(nb, cmd, exec);
	if (!top)
		return (pipeline_free(top), NULL);
	init_id(top);
	return (top);
}
