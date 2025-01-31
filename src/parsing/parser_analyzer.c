/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:16:05 by qupollet          #+#    #+#             */
/*   Updated: 2025/01/31 18:40:56 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "lexer.h"
#include "parsing.h"

int	ft_add_arg(t_cmd *cmd, char *arg)
{
	
}

int	ft_is_symbol(t_token *token, t_cmd *cmd)
{
	if (token->type == REDIRECT_IN)
		return (1);
	else if (token->type == REDIRECT_OUT)
		return (2);
	else if (token->type == APPEND)
		return (3);
	else if (token->type == HEREDOC)
		return (4);
	return (-1);
}

int	ft_token_analyzer(t_token *token, t_cmd *cmd)
{
	static int	redirect_mode = 0;

	if (!cmd || !token)
		return (-1);
	if (redirect_mode != 0)
	{
		if (token->type == REDIRECT_IN)
			cmd->infile = token->next;
		else if (token->type == REDIRECT_OUT)
			cmd->outfile = token->next;
		else if (token->type == APPEND)
		{
			cmd->append = 1;
			cmd->outfile = token->next;
		}
		else
			return (0);
	}
	else
		redirect_mode = ft_is_symbol(token, cmd);
	return (1);
}
