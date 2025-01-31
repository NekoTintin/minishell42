/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:16:05 by qupollet          #+#    #+#             */
/*   Updated: 2025/01/31 17:22:32 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "lexer.h"
#include "parsing.h"

int	ft_is_symbol(t_token *token, t_cmd *cmd)
{
	if (!cmd || !token)
		return (-1);
	if (token->type == REDIRECT_IN)
		cmd->infile = token->next->value;
	else if (token->type == REDIRECT_OUT)
		cmd->outfile = token->next->value;
	else
		return (0);
	return (1);
}
