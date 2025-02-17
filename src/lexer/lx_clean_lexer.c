/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_clean_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:16:44 by benoitchall       #+#    #+#             */
/*   Updated: 2025/02/20 20:11:51 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_lexer	*lx_clean_lexer(t_lexer *lexer)
{
	t_token	*curr;
	t_token	*free_node;

	curr = lexer->header;
	free_node = NULL;
	while (curr->next != NULL)
	{
		if (curr->next->type == WHITESPACE)
		{
			free_node = curr->next;
			curr->next = curr->next->next;
			free(free_node->value);
			free(free_node);
			lexer->size -= 1;
		}
		else
			curr = curr->next;
	}
	return (lexer);
}
