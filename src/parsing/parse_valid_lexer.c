/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_valid_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:38:35 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/23 17:32:41 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	valid_quote(t_lexer *lexer);
static int	valid_pipe(t_lexer *lexer);
int			valid_redirect(t_lexer *lexer);
t_token		*valid_skip_space(t_token *node);

int	parsing_valid_lexer(t_lexer *lexer)
{
	if (valid_quote(lexer) || valid_pipe(lexer) || valid_redirect(lexer))
		return (-1);
	return (0);
}

static int	valid_quote(t_lexer *lexer)
{
	t_token	*curr;
	int		d_quote;
	int		s_quote;

	curr = lexer->header;
	d_quote = 0;
	s_quote = 0;
	while (curr != NULL)
	{
		if (curr->type == D_QUOTES && d_quote == 0 && s_quote == 0)
			d_quote += 1;
		else if (curr->type == D_QUOTES && d_quote != 0 && s_quote == 0)
			d_quote -= 1;
		else if (curr->type == S_QUOTES && s_quote == 0 && d_quote == 0)
			s_quote += 1;
		else if (curr->type == S_QUOTES && s_quote != 0 && d_quote == 0)
			s_quote -= 1;
		curr = curr->next;
	}
	if (d_quote != 0 || s_quote != 0)
		return(printf("syntax error near quote\n"));
	return (0);
}

static int	valid_pipe(t_lexer *lexer)
{
	t_token	*curr;
	bool	pipe;

	pipe = false;
	curr = lexer->header;
	while (curr != NULL)
	{
		if (curr->type == PIPE && pipe == true)
			return (printf("%s %s »\n", ERORR, curr->value));
		if (curr->type == PIPE && pipe == false)
			pipe = true;
		if (curr->type != PIPE && curr->type != WHITESPACE)
			pipe = false;
		curr = curr->next;
		if (curr == NULL && pipe == true)
			return (printf("%s»\n", ERORR));
	}
	return (0);
}

int	valid_redirect(t_lexer *lexer)
{
	t_token	*node;

	node = lexer->header;
	while (node != NULL)
	{
		if (node_is_redirect(node))
		{
			if (node->next == NULL)
				return (printf("%s»\n", ERORR));
			while (node != NULL)
			{
				node = node->next;
				if (node == NULL)
					return (printf("%s»\n", ERORR));
				if (node_is_redirect(node))
					return (printf("%s %s »\n", ERORR, node->value));
				if (node->type == WORD)
					break ;
			}
		}
		else
			node = node->next;
	}
	return (0);
}

t_token	*valid_skip_space(t_token *node)
{
	while (node != NULL && node->type == WHITESPACE)
	{
		if (node->next == NULL)
			return (NULL);
		node = node->next;
	}
	if (node == NULL)
		return (NULL);
	return (node);
}
