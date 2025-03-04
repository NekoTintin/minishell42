/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arr_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:14:46 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/04 09:15:16 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	node_is_redirect(t_token *node);

int	parse_find_arrlen(t_token *node)
{
	int	index;

	index = 0;
	while (node != NULL)
	{
		if (node->type == WORD)
			index++;
		else if (node->type == VAR_ENV)
			index++;
		else if (node->type == PIPE)
			return (index);
		else if (node_is_redirect(node))
			return (index);
		node = node->next;
	}
	return (index);
}

static int	node_is_redirect(t_token *node)
{
	t_token_type	type;

	type = node->type;
	if (type == REDIRECT_IN || type == REDIRECT_OUT\
		|| type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}
