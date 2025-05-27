/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:17:11 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/27 17:26:30 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	search_redirect(t_cmd *cmd, t_token_type type)
{
	t_redirect	*cur;

	cur = cmd->redirect;
	while (cur)
	{
		if (cur->type == type)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int	ft_redirects(t_pipeline *pipeline)
{
	int		return_code;
	return (0);
}
