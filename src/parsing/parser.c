/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:36:40 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/05 19:43:42 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer		*join_quote(t_lexer *lexer);
t_token		*find_join(t_token *curr, t_token_type type);

t_parser	*mi_make_parse(t_parser *parse, t_lexer *lexer)
{
	if (lexer == NULL || lexer->header == NULL || parsing_valid_lexer(lexer))
		return (ll_free_lexer(lexer), NULL);
	else
	{
		lexer = parse_conc_quote(lexer);
		lexer = join_quote(lexer);
		if (lexer == NULL)
			return (ll_free_lexer(lexer), NULL);
		parse = parse_make_parser(parse);
		if (parse == NULL)
			return (ll_free_lexer(lexer), NULL);
		parse = parse_cmd_list(lexer->header, parse);
		if (parse == NULL)
			return (ll_free_lexer(lexer), NULL);
	}
	ll_free_lexer(lexer);
	return (parse);
}

t_lexer	*join_quote(t_lexer *lexer)
{
	char	*join;
	t_token	*curr;
	t_token	*node;

	join = NULL;
	node = NULL;
	curr = lexer->header;
	while (curr != NULL)
	{
		if (curr->type == S_QUOTES || curr->type == D_QUOTES)
		{
			node = curr->next;
			curr = find_join(curr, curr->type);
			if (curr == NULL)
				break ;
			if (curr->type == WORD || curr->type == VAR_ENV)
			{
				join = ft_strjoin(node->value, curr->value);
				free(node->value);
				node->value = ft_strdup(join);
				node->next = curr->next;
				curr = lexer->header;
			}
		}
		else
		{
			curr = curr->next;
		}
	}
	return (lexer);
}

t_token	*find_join(t_token *curr, t_token_type type)
{
	int	compt;

	compt = 0;
	while (curr != NULL)
	{
		if ((curr->type == WORD || curr->type == VAR_ENV) && compt == 3)
			return (curr);
		if (curr->type == type)
			compt++;
		if (compt == 4 || curr->type == WHITESPACE)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
