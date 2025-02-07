/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:32:21 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/07 18:18:27 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parsing.h"
#include "../../includes/minishell.h"

// Return the value of the specified environment variable 
char	*ft_get_from_env(char *env_var, char **envp)
{
	char	*no_dollar;
	char	*value;
	int		idx;
	int		size;

	if (!env_var || !envp || *envp == NULL || env_var[0] != '$')
		return (NULL);
	no_dollar = &env_var[1];
	size = ft_strlen(no_dollar);
	idx = 0;
	while (envp[idx])
	{
		if (ft_strncmp(envp[idx], no_dollar, size) == 0
			&& envp[idx][size] == '=')
		{
			value = ft_strdup(&envp[idx][size + 1]);
			if (!value)
				return (NULL);
			return (value);
		}
		idx++;
	}
	return (NULL);
}

// Count the number of pipes + 1 because of the first cmd
int	ft_command_counter(t_lexer *lexer)
{
	int			nb_command;
	t_token		*token;

	if (!lexer || !lexer->header)
		return (-1);
	token = lexer->header;
	while (token)
	{
		if (token->type == PIPE)
			nb_command++;
		token = token->next;
	}
	nb_command++;
	return (nb_command);
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
