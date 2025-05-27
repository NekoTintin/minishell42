/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:50:51 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/26 21:53:44 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_child(t_pipeline *pipeline)
{
	int		return_code;

	return_code = ft_find_in_envp(pipeline->cmd->argument[0], );
}

t_pipeline	*ft_create_pipeline(int nb, t_cmd *cmd)
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

int	exec_main(t_parser *parser, char **envp)
{
	t_exec	*exec;

	if (!parser || !parser->top || !parser->top->argument[0])
		return (1);
	exec = ft_calloc(1, sizeof(t_exec));
	if (!exec)
		return (1);
	exec->nb_child = parser->size;
	exec->envp = envp;
	exec->top = ft_create_pipeline(exec->nb_child, parser->top);
	if (!exec->top)
		return (ft_free_pipeline(exec->top), 1);
	return (0);
}
