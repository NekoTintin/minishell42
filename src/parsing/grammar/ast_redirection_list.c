/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redirection_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:25:26 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/03 08:26:56 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ast_redirection_list(t_token *node)
{
	while (node->type == REDIRECT_IN \
		|| node->type == REDIRECT_OUT \
		|| node->type == APPEND\
		|| node->type == HEREDOC)
	{
		node = parse_redirection(node);
		if (node == NULL)
			return (NULL);	
	}
	return (node);
}