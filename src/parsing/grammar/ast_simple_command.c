/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_simple_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:25:44 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/03 08:26:31 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ast_simple_cmd(t_token *node)
{
	
	printf("command: %s ", node->value);
	node = node->next;
	if (node == NULL)
		return (NULL);
	return (node);
}