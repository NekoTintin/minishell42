/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:53:30 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/24 14:19:51 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	search_red(t_cmd *cmd, t_token_type type)
{
	t_redirect	*cur;

	cur = cmd->redirect;
	while (cur)
	{
		if (cur->type == type)
			return (1);
		cur = cur->next;
	}
	return (0);
}

void	free_heredoc(t_cmd *top)
{
	t_cmd		*cur;

	if (!top)
		return ;
	cur = top;
	while (cur)
	{
		if (cur->heredoc)
		{
			if (unlink(cur->heredoc) == -1)
				perror("unlink");
			free(cur->heredoc);
			cur->heredoc = NULL;
		}
		cur = cur->next;
	}
}
