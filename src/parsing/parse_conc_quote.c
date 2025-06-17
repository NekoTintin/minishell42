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

static char			*make_value_in_quote(char *value, t_token *q_node);
static t_token		*make_new_quote(t_token *node);
static char	*loop_value(char *value, t_token *q_node, t_token *node, t_token *f_node);

t_lexer	*parse_conc_quote(t_lexer *lexer)
{
	t_token	*node;

	node = lexer->header;
	while (node != NULL)
	{
		if (node->type == D_QUOTES || node->type == S_QUOTES)
		{
			node = make_new_quote(node);
			if (node == NULL)
				return (ll_free_lexer(lexer), NULL);
		}
		node = node->next;
	}
	return (lexer);
}

static t_token	*make_new_quote(t_token *node)
{
	t_token		*q_node;
	t_token		*new;
	t_token		*f_node;
	char		*value;

	if (node->type == node->next->type)
		return (node->next);
	q_node = node->next;
	new = NULL;
	new = ll_init_tolken(new);
	value = NULL;
	f_node = NULL;
	/*while (q_node->type != node->type)
	{
		value = make_value_in_quote(value, q_node);
		if (value == NULL)
			return (NULL);
		f_node = q_node;
		q_node = q_node->next;
		free(f_node->value);
		free(f_node);
	}*/
	loop_value(value, q_node, node, f_node);
	new->value = ft_strdup(value);
	new->next = q_node;
	new->type = WORD;
	node->next = new;
	return (free(value), q_node);
}

static char	*loop_value(char *value, t_token *q_node, t_token *node, t_token *f_node)
{
	while (q_node->type != node->type)
	{
		value = make_value_in_quote(value, q_node);
		if (value == NULL)
			return (NULL);
		f_node = q_node;
		q_node = q_node->next;
		free(f_node->value);
		free(f_node);
	}
	return(value);
}

static char	*make_value_in_quote(char *value, t_token *q_node)
{
	char	*join;

	if (value == NULL)
		return (ft_strdup(q_node->value));
	join = ft_strjoin(value, q_node->value);
	return (free(value), join);
}
