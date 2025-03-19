/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:14:46 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/05 09:38:10 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_find_arrlen(t_token *node)
{
	int	index;

	index = 0;
	while (node != NULL)
	{
		if (node->type == WORD || node->type == WHITESPACE)
			index++;
		else if (node->type == VAR_ENV)
			index++;
		else if (node->type == PIPE)
			return (index);
		node = node->next;
	}
	return (index);
}

int	node_is_redirect(t_token *node)
{
	t_token_type	type;

	type = node->type;
	if (type == REDIRECT_IN || type == REDIRECT_OUT \
		|| type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}

int	node_is_ascii(t_token *node)
{
	t_token_type	type;

	type = node->type;
	if (type == D_QUOTES || type == S_QUOTES \
		|| type == WHITESPACE || type == WORD || type == VAR_ENV)
		return (1);
	return (0);
}

t_cmd	*last_command(t_parser *parse)
{
	t_cmd	*curr;

	curr = parse->top;
	while (curr->next != NULL)
		curr = curr->next;
	return (curr);
}

t_parser	*add_command(t_parser *parse)
{
	t_cmd	*node;
	t_cmd	*last_node;

	node = NULL;
	node = parse_make_command(node);
	if (node == NULL)
		return (free_all_parser(parse), NULL);
	if (parse->top == NULL)
	{
		parse->top = node;
		parse->size += 1;
		return (parse);
	}
	else
	{
		last_node = last_command(parse);
		last_node->next = node;
		parse->size += 1;
	}
	return (parse);
}
