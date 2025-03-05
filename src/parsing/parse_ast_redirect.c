/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:14:28 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/05 19:50:51 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*parse_redirection_list(t_token *node, t_cmd *cmd)
{
	t_redirect	*redirect;

	cmd = parse_add_redirect(cmd);
	redirect = last_redirect(cmd);
	redirect->type = node->type;
	while (node->type != WORD)
	{
		node = node->next;
		if (node == NULL)
			return (NULL);
	}
	node = parse_redirection(node, redirect);
	if (node == NULL)
		return (NULL);
	return (node);
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
	redirect->file[1] = NULL;
	return (node);
}
