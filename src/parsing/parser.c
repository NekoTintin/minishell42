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
t_token		*conc_quote(t_token *curr, t_lexer *lexer);
t_lexer		*ll_delet_type(t_lexer *lexer, t_token_type type);
t_token	*conc_node_word(t_token *curr, t_lexer *lexer);
t_lexer	*conc_word(t_lexer *lexer);
t_token	*ll_delet_token(t_token *node);

t_parser	*mi_make_parse(t_parser *parse, t_lexer *lexer)
{
	if (lexer == NULL || lexer->header == NULL || parsing_valid_lexer(lexer))
		return (ll_free_lexer(lexer), NULL);
	else
	{
		lexer = parse_conc_quote(lexer);
		lexer = ll_delet_type(lexer, S_QUOTES);
		lexer = ll_delet_type(lexer, D_QUOTES);
		lexer = conc_word(lexer);
		//lexer = join_quote(lexer);
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
	print_parse(parse);
	return (parse);
}

t_lexer	*ll_delet_type(t_lexer *lexer, t_token_type type)
{
	t_token	*delete;

	delete = lexer->header;
	while (delete->next != NULL)
	{
		if (delete->next->type == type)
			delete = ll_delet_token(delete);
		else
			delete = delete->next;
	}
	return (lexer);
}

t_token	*ll_delet_token(t_token *node)
{
	t_token	*buffer;

	buffer = NULL;
	if (node == NULL || node->next == NULL)
		return (NULL);
	buffer = node->next;
	node->next = node->next->next;
	free(buffer->value);
	free(buffer);
	return(node);
}

t_lexer	*conc_word(t_lexer *lexer)
{
	t_token	*curr;

	curr = lexer->header;
	while (curr != NULL)
	{
		if (curr->type == WHITESPACE && \
			curr->next != NULL && curr->next->type == WORD)
			curr = conc_node_word(curr, lexer);
		else
			curr = curr->next;
	}
	return (lexer);
}
t_token	*conc_node_word(t_token *curr, t_lexer *lexer)
{	
	char	*join;
	t_token	*node;

	if (curr->type == WHITESPACE && curr->next != NULL)
	{
		node = curr->next; // ici mon mot;
		if (curr->next->next == NULL || curr->next->next->type != WORD)
			return (curr->next);
		curr = curr->next->next;
		join = ft_strjoin(node->value, curr->value);
		if (join == NULL)
			return (NULL);
		free(node->value);
		node->value = ft_strdup(join);
		if (node->value == NULL)
			return (NULL);
		node->next = curr->next;
		free(curr->value);
		free(curr);
		free(join);
		return (lexer->header);
	}
	return (curr->next);
}

