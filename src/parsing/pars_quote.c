/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:20:04 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/02/28 14:17:04 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pars_quote(t_lexer *lexer)
{
	int		error_code;
	char		*str;
	char		*new;
	t_token		*curr;
	t_token		*node;
	t_token 	*quote;

	error_code = 0;
	str = NULL;
	new = NULL;
	curr = lexer->header;
	node = NULL;


	while (curr != NULL)
	{
		if (curr->type == D_QUOTES || curr->type == S_QUOTES)
		{
			node = curr->next;
			new = ft_strjoin("", node->value);
			node = node->next;
			while (node->type != curr->type)
			{
				str = ft_strdup(new);
				free(new);
				printf("str = %s", str);
				new = ft_strjoin(str, node->value);
				node = node->next;
				free(str);
			}
			quote = ll_init_tolken(quote);

			quote->value = new;
			quote->type = WORD;
			quote->next = node;
			curr->next = quote;
			curr = node->next;
		}
		else
			curr = curr->next;
	}
	printf("-- out fonction quote --\n");
	return (error_code);
}
