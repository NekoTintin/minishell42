/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:16:05 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/03 17:24:42 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "lexer.h"
#include "parsing.h"

// Reallocate and add an string to the cmd->args
int	ft_add_arg(t_cmd *cmd, char *arg)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (tab && tab[i])
		i++;
	new_tab = ft_calloc(i + 2, sizeof(char *));
	if (!new_tab)
		return (-1);
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_tab[i] = cmd->args[i];
		i++;
	}
	new_tab[i] = ft_strdup(arg);
	if (!new_tab[i])
		return (free(new_tab), -1);
	free(cmd->args);
	cmd->args = new_tab;
	return (0);
}

int	ft_get_symbol(t_token *token)
{
	if (token->type == REDIRECT_IN)
		return (1);
	else if (token->type == REDIRECT_OUT)
		return (2);
	else if (token->type == APPEND)
		return (3);
	else if (token->type == HEREDOC)
		return (4);
	return (0);
}

void	ft_handle_words(t_token *token, t_cmd *cmd)
{
	
}
