/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:16:05 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/07 19:01:17 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "lexer.h"
#include "parsing.h"

// Reallocate and add an string to the cmd->args
int	ft_add_arg(char ***tab, char *arg)
{
	char	**new_tab;
	int		i;

	if (!*tab)
	{
		*tab = ft_calloc(2, sizeof(char));
		if (!*tab)
			return (-1);
	}
	i = 0;
	while ((*tab)[i])
		i++;
	new_tab = ft_calloc(i + 2, sizeof(char *));
	if (!new_tab)
		return (-1);
	i = -1;
	while ((*tab)[++i])
		new_tab[i] = (*tab)[i];
	new_tab[i] = ft_strdup(arg);
	if (!new_tab[i])
		return (free(new_tab), -1);
	free(*tab);
	*tab = new_tab;
	return (0);
}

int	ft_add_to_append(int **tab, int value)
{
	int		*new_tab;
	int		i;

	if (!*tab)
	{
		*tab = ft_calloc(2, sizeof(int));
		if (!*tab)
			return (-1);
		(*tab)[0] = value;
		(*tab)[1] = -1;
		return (0);
	}
	i = 0;
	while ((*tab)[i] != -1)
		i++;
	new_tab = ft_calloc(i + 2, sizeof(int));
	if (!new_tab)
		return (-1);
	new_tab[i] = value;
	new_tab[i + 1] = -1;
	while (i--)
		new_tab[i] = (*tab)[i];
	free(*tab);
	*tab = new_tab;
	return (0);
}

int	ft_handle_symbol(t_token *token, t_cmd *cmd)
{
	int		temp_value;

	if (token->type == REDIRECT_OUT || token->type == REDIRECT_APPEND)
	{
		if (ft_add_arg(&cmd->outfile, token->next->value) == -1)
			return (-1);
		if (token->type == REDIRECT_OUT)
			temp_value = 0;
		else
			temp_value = 1;
		if (ft_add_to_append(&cmd->append, temp_value) == -1)
			return (-1);
	}
	else if (token->type == REDIRECT_IN)
	{
		if (ft_add_arg(&cmd->infile, token->next->value) == -1)
			return (-1);
	}
	return (0);
}

int	ft_handle_words(t_token *token, t_cmd *cmd)
{
	cmd->is_builtin = ft_is_builtin(token->value);
	if (ft_add_arg(cmd, token->value) == -1)
		return (-1);
}
