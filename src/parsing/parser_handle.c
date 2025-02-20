/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:16:05 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/20 19:51:44 by qupollet         ###   ########.fr       */
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
	if (!token->next)
		return (-1);
	if (ft_strncmp(token->next->value, "-", 1) == 0
		&& token->next->value[1] == '\0')
	{
		cmd->delete_tabs = 1;
		cmd->delimiter = ft_strdup(token->next->next->value);
		if (!cmd->delimiter)
			return (-1);
	}
	else
	{
		cmd->delete_tabs = 0;
		cmd->delimiter = ft_strdup(token->next->value);
		if (!cmd->delimiter)
			return (-1);
	}
	return (0);
}

int	ft_handle_symbol(t_token *token, t_cmd *cmd)
{
	int		temp_value;

	if (token->next == NULL)
		return (-1);
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
		if (ft_heredoc_case(token, cmd) == -1)
			return (-1);
	return (0);
}

int	ft_handle_word(t_token *token, t_cmd *cmd, char **envp)
{
	cmd->is_builtin = ft_is_builtin(token->value);
	if (token->type == S_QUOTES || token->type == D_QUOTES)
		if (remove_quotes(token) == -1)
			return (-1);
	if (token->type == VAR_ENV || token->type == D_QUOTES
		|| (token->type == WORD))
	{
		if (ft_replace_env(token, envp) == -1)
			return (-1);
		if (ft_add_arg(&cmd->args, token->value) == -1)
			return (-1);
	}
	else
		if (ft_add_arg(&cmd->args, token->value) == -1)
			return (-1);
	return (0);
}
