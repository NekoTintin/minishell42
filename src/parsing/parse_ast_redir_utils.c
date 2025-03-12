/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast_redir_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:27:17 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/05 13:50:04 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_redirect	*last_redirect(t_cmd *cmd)
{
	t_redirect	*curr;

	curr = cmd->redirect;
	while (curr->next != NULL)
		curr = curr->next;
	return (curr);
}

t_cmd	*parse_add_redirect(t_cmd *cmd)
{
	t_redirect	*node;
	t_redirect	*l_node;

	node = NULL;
	node = parse_make_redirect(node);
	if (node == NULL)
		return (NULL);
	if (cmd->redirect == NULL)
	{
		cmd->redirect = node;
		return (cmd);
	}
	else
	{
		l_node = last_redirect(cmd);
		l_node->next = node;
	}
	return (cmd);
}

t_token	*parse_redirection_herdoc(t_token *node, t_redirect *redirect)
{
	int	i;
	int	j;

	j = 0;
	i = parse_herdoclen(node);
	redirect->file = ft_calloc(i + 1, sizeof(char *));
	while (j < i)
	{
		redirect->file[j] = ft_strdup(node->value);
		j++;
		if (node->next == NULL)
			return (NULL);
		if (!node_is_ascii(node->next))
			return (node);
		node = node ->next;
	}
	return (node);
}
