/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:23:23 by benoitchall       #+#    #+#             */
/*   Updated: 2025/06/25 12:52:28 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*loop_parse_cmd(t_token *node, t_cmd *cmd);

t_parser	*parse_cmd_list(t_token *node, t_parser *parse)
{
	while (node != NULL)
	{
		parse = add_command(parse);
		if (parse->top == NULL)
			return (NULL);
		node = parse_commande(node, last_command(parse));
		if (node == NULL)
			return (parse);
		if (node->type != PIPE)
			return (NULL);
		node = node->next;
	}
	return (parse);
}

t_token	*parse_commande(t_token *node, t_cmd *cmd)
{
	cmd->argument = ft_calloc(parse_find_arrlen(node) + 1, sizeof(char *));
	if (cmd->argument == NULL)
		return (NULL);
	node = loop_parse_cmd(node, cmd);
	return (node);
}

t_token	*loop_parse_cmd(t_token *node, t_cmd *cmd)
{
	int	index;

	index = 0;
	while (node->type != PIPE)
	{
		if (node->type == WORD || node->type == VAR_ENV)
		{
			if (node->value[0] != '\0')
				cmd->argument[index++] = parse_simple_cmd(node);
			if (cmd == NULL)
				return (NULL);
		}
		else if (node_is_redirect(node))
		{
			node = parse_redirection_list(node, cmd);
			if (node == NULL)
				return (NULL);
		}
		node = node->next;
		if (node == NULL)
			return (NULL);
	}
	return (node);
}

char	*parse_simple_cmd(t_token *node)
{
	char	*args;

	if (node->type == WORD || node->type == WHITESPACE
		|| node->type == VAR_ENV)
	{
		args = ft_strdup(node->value);
		if (args == NULL)
			return (NULL);
	}
	else
		return (NULL);
	return (args);
}
