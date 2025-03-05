/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:14:28 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/05 11:36:16 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_redirect	*last_redirect(t_cmd *cmd);
t_cmd	*parse_add_redirect(t_cmd *cmd);
t_token	*parse_redirection_herdoc(t_token *node, t_redirect *redirect);

/*t_token	*parse_redirection_list(t_token *node, t_cmd *cmd)
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
}*/

t_token	*parse_redirection_list(t_token *node, t_cmd *cmd)
{
	t_redirect	*redirect;
	
	cmd = parse_add_redirect(cmd);
	redirect = last_redirect(cmd);
	redirect->type = node->type;
	printf("-- test(0)-->\n");
	while (node->type != WORD)
	{
		node = node->next;
		if (node == NULL)
			return(NULL);
	}
	node = parse_redirection(node, redirect);
	if (node == NULL)
		return (NULL);
	return (node);

}

int	parse_herdoclen(t_token *node)
{
	int	size;

	size = 0;
	while (node != NULL)
	{
		printf("test lop %s\n", node->value);
		if (!node_is_ascii(node))
			return (size);
		size++;
		node = node->next;
	}
	return (size);
}

t_token	*parse_redirection(t_token *node, t_redirect *redirect)
{

	if (redirect->type == HEREDOC)
		return (parse_redirection_herdoc(node, redirect));
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
		return(cmd);
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

	i = 0;
	j = 0;
	i = parse_herdoclen(node);
	printf("-- i = %d --\n", i);
	redirect->file = (char **)malloc(sizeof(char *) * i + 1);
	while (j < i)
	{

		printf("-- test(01)-->%s |i =%d, j=%d\n",node->value, i, j);
		//redirect->file[j] = ft_strdup(node->value);
		j++;
		node = node ->next;
		printf("-- test (1)-->%s\n", node->value);
	}
	return (node);
}
