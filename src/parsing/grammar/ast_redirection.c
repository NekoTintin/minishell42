/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:25:39 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/03 08:27:13 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ast_redirection(t_token *node)
{
	while (node != NULL)
	{
		if (node->type == REDIRECT_IN)
			printf("is redirect int ");
		else if (node->type == REDIRECT_OUT)
			printf("is redirection out ");
		else if (node->type == APPEND)
			printf("append ");
		else if (node->type == HEREDOC)
			printf("is heredoc ");
		else if (node->type == WORD)
			printf("redirction: %s", node->value);
		else if (node ->type == PIPE)
			return (node);
		else if (node == NULL)
			return (NULL);
		node = node->next;
	}
	return (node);
}
