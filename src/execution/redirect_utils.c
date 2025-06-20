/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:05:03 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/20 18:13:41 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_heredoc(t_exec *exec)
{
	if (!exec)
		return ;
	if (exec->mini->parse)
		free_all_parser(exec->mini->parse);
	free(exec->mini);
	if (exec->env)
	{
		ft_free_env(exec->env);
		exec->env = NULL;
	}
	free_exec(exec);
	clear_history();
}
