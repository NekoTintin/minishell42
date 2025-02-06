/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:16:05 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/06 01:08:37 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "lexer.h"
#include "parsing.h"

int	ft_is_builtin(const char *str)
{
	if (ft_strncmp(str, "echo", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "cd", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "export", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "unset", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "env", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "exit", ft_strlen(str)) == 0)
		return (1);
	return (0);
}

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

int	ft_handle_symbol(t_token *token, t_cmd *cmd)
{
	if (token->type == REDIRECT_OUT)
	{
		cmd->outfile = token->next->value;
		if (!cmd->outfile)
			return (-1);
		cmd->append
	}
}

int	ft_handle_words(t_token *token, t_cmd *cmd)
{
	cmd->is_builtin = ft_is_builtin(token->value);
	if (ft_add_args(cmd, token->value) == -1)
		return (-1);
}
