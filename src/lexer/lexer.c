/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 03:57:57 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/12 15:39:50 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static t_lexer	*lx_value_chain(char *string, t_lexer *lexer);
static t_lexer	*lx_tolkenization(t_lexer *lexer);
static int		lx_assing_type(t_token *node);

t_lexer	*mi_make_lexer(char *readline_string)
{
	t_lexer	*lexer;

	lexer = NULL;
	lexer = ll_init_lexer(lexer);
	if (lexer == NULL || readline_string == NULL)
		return (NULL);
	lexer = lx_value_chain(readline_string, lexer);
	if (lexer == NULL)
		return (NULL);
	lexer = lx_tolkenization(lexer);
	if (lexer == NULL)
		return (NULL);
	return (lexer);
}

static t_lexer	*lx_value_chain(char *string, t_lexer *lexer)
{
	int			index;

	index = 0;
	while (string[index] != '\0')
	{
		if (string[index] == 32)
			index = lx_space_token(index, lexer);
		else
			index = lx_value_node(index, string, lexer);
		if (index == -1)
			return (NULL);
	}
	return (lexer);
}

static t_lexer	*lx_tolkenization(t_lexer *lexer)
{
	t_token	*curr;
	int		error_code;

	curr = lexer->header;
	while (curr != NULL)
	{
		if (curr->type != WHITESPACE)
		{
			error_code = lx_assing_type(curr);
			if (error_code == -1)
				return (ll_free_lexer(lexer), NULL);
		}
		curr = curr->next;
	}
	return (lexer);
}

static int	lx_assing_type(t_token *node)
{
	int	error_code;

	error_code = 0;
	if (node->value[0] == '<' || node->value[0] == '>' || node->value[0] == '|')
		return (error_code = lx_assing_synbols(node));
	else if (node->value[0] == '$')
		return (error_code = lx_assing_env(node));
	else if (node->value[0] == 34 || node->value[0] == 39)
		return (error_code = lx_assing_quotes(node));
	else if (ft_isascii(node->value[0]))
		return (error_code = lx_assing_word(node));
	return (-1);
}
