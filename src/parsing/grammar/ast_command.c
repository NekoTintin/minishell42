/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:25:17 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/03 08:27:34 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ast_commande(t_token *node)
{
	while (node->type != PIPE)
	{
		if (node->type == WORD)
			node = parse_simple_cmd(node);
		else if (node->type == REDIRECT_IN \
			|| node->type == REDIRECT_OUT \
			|| node->type == APPEND \
			|| node->type == HEREDOC)
			node = parse_redirection_list(node);
		else
			node = node->next;
		if (node == NULL)
			return (NULL);
	}
	return (node);
}