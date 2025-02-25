/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:48:04 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/25 15:29:35 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_lexer	*lx_dup_str(char *dup_str, t_lexer *lexer);
static int		lx_test_c(char *c);
static int		lx_find_length(char *string, int index, int length);

int	lx_space_token(int index, t_lexer *lexer)
{
	t_token	*node;

	lexer = ll_add_token(lexer);
	if (lexer == NULL)
		return (-1);
	node = ll_last_token(lexer);
	node->value = ft_strdup(" ");
	node->type = WHITESPACE;
	return (index + 1);
}

int	lx_value_node(int index, char *string, t_lexer *lexer)
{
	int		length;
	int		index_dup;
	char	*dup_str;

	length = 0;
	length = lx_find_length(string, index, length);
	dup_str = (char *)malloc(sizeof(char) * (length + 1));
	if (dup_str == NULL)
		return (ll_free_lexer(lexer), -1);
	index_dup = 0;
	while (index_dup != length)
	{
		dup_str[index_dup] = string[index + index_dup];
		index_dup++;
	}
	dup_str[index_dup] = '\0';
	lexer = lx_dup_str(dup_str, lexer);
	if (lexer == NULL)
		return (-1);
	return (index + length);
}

static t_lexer	*lx_dup_str(char *dup_str, t_lexer *lexer)
{
	t_token	*node;

	lexer = ll_add_token(lexer);
	if (lexer == NULL)
		return (NULL);
	node = ll_last_token(lexer);
	node->value = dup_str;
	return (lexer);
}

static int	lx_test_c(char *c)
{
	if (*c == '>' || *c == '|' || *c == '<' \
		|| *c == 32 || *c == 36 || *c == 39 || *c == 34)
		return (1);
	return (0);
}

static int	lx_find_length(char *str, int index, int length)
{
	if (str[index] == '<' || str[index] == '>')
	{
		while (str[index + length] == str[index])
			length++;
		return (length);
	}
	else if (str[index] == 39 || str[index] == 34  || str[index] == '|')
	{
		length = 1;
		return (length);
	}
	else if (str[index] == 36)
	{
		length = 1;
		while (!lx_test_c(&str[index + length]) && str[index + length] != '\0')
			length++;
		return (length);
	}
	while (str[index + length] != '\0' && !lx_test_c(&str[index + length]))
		length++;
	return (length);
}
