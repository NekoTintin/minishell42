/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chain_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 08:53:05 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/21 11:34:58 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*ll_init_lexer(t_lexer *lexer)
{
	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (lexer == NULL)
		return (NULL);
	lexer->header = NULL;
	lexer->size = 0;
	return (lexer);
}

t_token	*ll_init_tolken(t_token *node)
{
	node = (t_token *)malloc(sizeof(t_token));
	if (node == NULL)
		return (NULL);
	node->value = NULL;
	node->next = NULL;
	node->type = UNKNOWN;
	return (node);
}

t_lexer	*ll_add_token(t_lexer *lexer)
{
	t_token	*node;
	t_token	*last;

	node = NULL;
	node = ll_init_tolken(node);
	if (node == NULL)
		return (ll_free_lexer(lexer), NULL);
	if (lexer->header == NULL)
	{
		lexer->header = node;
		lexer->size += 1;
		return (lexer);
	}
	else
	{
		last = ll_last_token(lexer);
		last->next = node;
		lexer->size += 1;
	}
	return (lexer);
}

t_token	*ll_last_token(t_lexer *lexer)
{
	t_token	*current;

	current = lexer->header;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void	ll_free_lexer(t_lexer *lexer)
{
	t_token	*free_node;

	while (lexer->header != NULL)
	{
		free_node = lexer->header;
		lexer->header = lexer->header->next;
		free(free_node->value);
		free(free_node);
	}
	free(lexer);
}
