/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:16:05 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/17 19:25:48 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parsing.h"

// Reallocate and add an string to the cmd->args
int	ft_add_arg(char ***table, char *arg)
{
	char	**new_tab;
	int		i;

	if (!*table)
	{
		*table = ft_calloc(2, sizeof(char *));
		if (!*table)
			return (-1);
	}
	i = 0;
	while ((*table)[i])
		i++;
	new_tab = ft_calloc(i + 2, sizeof(char *));
	if (!new_tab)
		return (-1);
	i = -1;
	while ((*table)[++i])
		new_tab[i] = (*table)[i];
	new_tab[i] = ft_strdup(arg);
	if (!new_tab[i])
		return (free(new_tab), -1);
	free(*table);
	*table = new_tab;
	return (0);
}

int	ft_add_to_append(int **table, int value)
{
	int		*new_tab;
	int		i;

	if (*table == NULL)
	{
		*table = ft_calloc(2, sizeof(int));
		if (!*table)
			return (-1);
		(*table)[0] = value;
		(*table)[1] = -1;
		return (0);
	}
	i = 0;
	while ((*table)[i] != -1)
		i++;
	new_tab = ft_calloc(i + 2, sizeof(int));
	if (!new_tab)
		return (-1);
	new_tab[i] = value;
	new_tab[i + 1] = -1;
	while (i--)
		new_tab[i] = (*table)[i];
	free(*table);
	*table = new_tab;
	return (0);
}

int	ft_heredoc_case(t_token *token, t_cmd *cmd)
{
	(void)token;
	(void)cmd;
	return (0);
}

int	ft_handle_symbol(t_token *token, t_cmd *cmd)
{
	int		temp_value;

	if (token->type == REDIRECT_OUT || token->type == APPEND)
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
	else if (token->type == HEREDOC)
	{
		if (ft_heredoc_case(token, cmd) == -1)
			return (-1);
	}
	return (0);
}

int	ft_handle_word(t_token *token, t_cmd *cmd)
{
	cmd->is_builtin = ft_is_builtin(token->value);
	if (ft_add_arg(&cmd->args, token->value) == -1)
		return (-1);
	return (0);
}
