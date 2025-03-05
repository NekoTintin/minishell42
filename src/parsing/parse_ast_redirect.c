/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:14:28 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/05 09:19:38 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*parse_redirection_list(t_token *node, t_cmd *cmd)
{
	t_redirect	*redirect;

	redirect = NULL;
	cmd->redirect = parse_make_redirect(redirect);
	redirect = cmd->redirect;
	while (node_is_redirect(node) && node != NULL)
	{
		redirect->type = node->type;
		while (node->type != WORD)
			node = node->next;
		node = parse_redirection(node, redirect);
		if (node == NULL)
            return (node);
	}
	return (node);
}

int	parse_herdoclen(t_token *node)
{
	int	size;

	size = 0;
	while (node != NULL)
	{
		if (!node_is_ascii(node))
			return (size);
		size++;
		node = node->next;
	}
	return (size);
}

t_token	*parse_redirection(t_token *node, t_redirect *redirect)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (redirect->type == HEREDOC)
	{
		i = parse_herdoclen(node);
		redirect->file = (char **)malloc(sizeof(char *) * i + 1);
		while (j != i)
		{
			redirect->file[j] = ft_strdup(node->value);
			j++;
			node = node ->next; 
		}
		return (node);
	}
	else
	{
		redirect->file = (char **)malloc(sizeof(char *) * 2);
		if (redirect->type == REDIRECT_IN)
			redirect->file[i] = ft_strdup(node->value);
		if (redirect->type == REDIRECT_OUT)
			redirect->file[i] = ft_strdup(node->value);
		if (redirect->type == APPEND)
			redirect->file[i] = ft_strdup(node->value);
	}
	node = node->next;
	return (node);
}
