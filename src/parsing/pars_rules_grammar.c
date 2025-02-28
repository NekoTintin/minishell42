/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_rules_grammar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:23:23 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/02/28 10:23:26 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	CommandList -> Command | Command '|' CommandList
	Command -> SimpleCommand RedirectionList
	SimpleCommand -> WORD SimpleCommand | WORD
	RedirectionList -> Redirection RedirectionList | ε
	Redirection -> '<' WORD | '>' WORD | '>>' WORD | ...
*/

t_token	*parse_simple_cmd(t_token *node)
{
	printf("cmd : %s \n", node->value);
	node = node->next;
	if (node == NULL)
		return (NULL);
	return (node);
}

t_token	*parse_cmd_list(t_token *node)
{
	while (node->type != PIPE)
	{
		node = parse_commande(node);
		if (node == NULL)
			return (NULL);
	}
	return (node);
}

t_token	*parse_commande(t_token *node)
{
	while (node->type != PIPE)
	{
		if (node->type == WORD)
			node = parse_simple_cmd(node);
		else if (node->type == REDIRECT_IN \
			|| node->type == REDIRECT_OUT \
			|| node->type == APPEND \
			|| node->type == HEREDOC)
			node = parse_redirection_list(node);
		else
			node = node->next;
		if (node == NULL)
			return (NULL);
		printf("test: %s\n", node->value);
	}
	return (node);
}

t_token	*parse_redirection_list(t_token *node)
{
	if (node->type == REDIRECT_IN)
		printf("is redirect int\n");
	else if (node->type == REDIRECT_OUT)
		printf("is redirection out\n");
	else if (node->type == APPEND)
		printf("append\n");
	else if (node->type == HEREDOC)
		printf("is heredoc\n");
	node = node->next;
	if (node == NULL)
		return (NULL);
	return (node);
}
