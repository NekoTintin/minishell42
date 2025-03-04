/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_index_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 07:05:18 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/03 07:05:19 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*parse_index_lexer(t_lexer *lexer)
{
	int	index;
	t_token	*curr;

	index = 0;
	curr = lexer->header;
	if (lexer == NULL || curr == NULL)
		return (NULL);
	while (curr != NULL)
	{
		curr->index = index;
		index++;
		curr = curr->next;
	}
	return (lexer);
}
