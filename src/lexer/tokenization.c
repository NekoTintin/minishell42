/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:25:00 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/27 14:42:48 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	lx_assing_word(t_token *node)
{
	node->type = WORD;
	return (1);
}

int	lx_assing_synbols(t_token *node)
{
	if (ft_strlen(node->value) == 2)
	{
		if (node->value[1] == '>')
			node->type = APPEND;
		else if (node->value[1] == '<')
			node->type = HEREDOC;
		return (1);
	}
	else if (node->value[0] == '>')
		node->type = REDIRECT_OUT;
	else if (node->value[0] == '<')
		node->type = REDIRECT_IN;
	else if (node->value[0] == '|')
		node->type = PIPE;
	else
		return (-1);
	return (1);
}

int	lx_assing_env(t_token *node)
{
	node->type = VAR_ENV;
	return (0);
}

int	lx_assing_quotes(t_token *node)
{
	if (node->value[0] == 34)
		node->type = D_QUOTES;
	else if (node->value[0] == 39)
		node->type = S_QUOTES;
	else
		return (-1);
	return (0);
}
