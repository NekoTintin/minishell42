/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc_pipeline.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:28:10 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/22 20:54:34 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_prepare_heredoc(t_exec *exec)
{
	t_pipeline	*cur;
	t_redirect	*red;
	int			code;

	cur = exec->top;
	while (cur)
	{
		red = cur->cmd->redirect;
		while (red)
		{
			if (red->type == HEREDOC)
			{
				code = exec_heredoc(red, cur->heredoc_pipe, exec);
				if (code != 0)
					return (code);
			}
			red = red->next;
		}
		cur = cur->next;
	}
	return (0);
}
