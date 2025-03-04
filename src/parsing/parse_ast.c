/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:23:23 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/04 15:39:42 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	CommandList -> 		Command | Command '|' CommandList
	Command -> 		SimpleCommand RedirectionList
	SimpleCommand -> 	WORD SimpleCommand | WORD
	RedirectionList -> 	Redirection RedirectionList | ε
	Redirection -> 		'<' WORD | '>' WORD | '>>' WORD | ...
*/

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
	int	index;

	
	index = 0;
	cmd->argument = (char **)malloc(sizeof(char *) * parse_find_arrlen(node) + 1);
	while (node->type != PIPE)
	{
		if (node->type == WORD || node->type == VAR_ENV)
		{	
			cmd->argument[index] = parse_simple_cmd(node);
			if (cmd == NULL)
				return (NULL);
			index++;	
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

char 	*parse_simple_cmd(t_token *node)
{
	char	*args;

	if (node->type == WORD || node->type == VAR_ENV)
	{
		args = ft_strdup(node->value);
		if (args == NULL)
			return (NULL);
	}
	else
		return (NULL);
	return (args);
}

t_token	*parse_redirection_list(t_token *node, t_cmd *cmd)
{
	t_redirect	*redirect;

	redirect = NULL;
	cmd->redirect = parse_make_redirect(redirect);
	redirect = cmd->redirect;
	while (node_is_redirect(node) && node != NULL)
	{
		node = parse_redirection(node, redirect);
		while (node->type != WORD)
			node = node->next;
		node = parse_redirection_argument(node, redirect);
		return (node);
	}
	return (node);
}

t_token	*parse_redirection(t_token *node, t_redirect *redirect)
{
	if (node->type == REDIRECT_IN)
		redirect->type = REDIRECT_IN;
	else if (node->type == REDIRECT_OUT)
		redirect->type = REDIRECT_OUT;
	else if (node->type == APPEND)
		redirect->type = APPEND;
	else if (node->type == HEREDOC)
		redirect->type = HEREDOC;
	else
		redirect->type = UNKNOWN;
	return (node);
}

t_token	*parse_redirection_argument(t_token *node, t_redirect *redirect)
{
	if (redirect->type == HEREDOC)
		return (node->next);
	redirect->file = (char **)malloc(sizeof(char *) * 2);
	if (redirect->type == REDIRECT_IN)
		redirect->file[0] = ft_strdup(node->value);
	if (redirect->type == REDIRECT_OUT)
		redirect->file[0] = ft_strdup(node->value);
	if (redirect->type == APPEND)
		redirect->file[0] = ft_strdup(node->value);
	node = node->next;
	return (node);
}
