/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:53:30 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/24 14:00:21 by qupollet         ###   ########.fr       */
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
	if (top->heredoc)
	{
		if (unlink(top->heredoc) == -1)
			perror("unlink");
		free(top->heredoc);
		top->heredoc = NULL;
	}
}
