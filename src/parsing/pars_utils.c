/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:32:21 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/20 19:58:50 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Count the number of pipes + 1 because of the first cmd
int	ft_command_counter(t_lexer *lexer)
{
	int			nb_command;
	t_token		*token;

	if (!lexer || !lexer->header)
		return (-1);
	nb_command = 0;
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

int	remove_quotes(t_token *token)
{
	int		lenght;
	char	*new_value;

	if (token->type == S_QUOTES || token->type == D_QUOTES)
	{
		lenght = ft_strlen(token->value);
		new_value = ft_substr(token->value, 1, lenght - 2);
		if (new_value)
		{
			free(token->value);
			token->value = new_value;
			return (0);
		}
		return (-1);
	}
	return (0);
}
