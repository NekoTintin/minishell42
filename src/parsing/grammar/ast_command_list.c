/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_command_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:24:01 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/03 08:24:54 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ast_cmd_list(t_token *node)
{
	node = parse_commande(node);
	if (node == NULL)
		return (NULL);
	while (node->type == PIPE)
	{
		node = node->next;
		printf("\n");
		node = parse_commande(node);
		if (node == NULL)
			return (NULL);
	}
	return (node);
}