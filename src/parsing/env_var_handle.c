/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:01:06 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/20 20:29:28 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_if_exist(char *env, char **envp)
{
	char	*no_dollar;
	char	*no_env_dollar;
	int		key_len;
	int		idx;

	if (env[0] == '$')
		no_dollar = env + 1;
	else
		no_dollar = env;
	idx = 0;
	while (envp[idx])
	{
		key_len = 0;
		while (envp[idx][key_len] && envp[idx][key_len] != '=')
			key_len++;
		if (ft_strncmp(envp[idx], no_dollar, key_len) == 0
			&& envp[idx][key_len] == '=' && env[key_len] == '\0')
		{
			no_env_dollar = envp[idx] + (key_len + 1);
			return (no_env_dollar);
		}
		idx++;
	}
	return (NULL);
}

int	get_size(char *str, char **envp)
{
	int		total;
	int		idx;
	char	*env_value;

	total = 0;
	idx = 0;
	while (str[idx])
	{
		if (str[idx] == '$')
		{
			env_value = get_env_value(str + idx + 1, envp);
			if (env_value)
				total += ft_strlen(env_value);
			while (str[++idx] && str[idx] != ' ' && str[idx] != '$')
				idx++;
		}
		else
		{
			total++;
			idx++;
		}
	}
	return (total);
}

void	env_var_loop(char *str, char **new_str, char **envp)
{
	int		idx;
	int		idx2;
	int		var_len;
	char	*env_value;

	idx = 0;
	idx2 = 0;
	while (str[idx])
	{
		if (str[idx] == '$')
		{
			var_len = 0;
			while (str[idx + var_len + 1] != ' '
				&& str[idx + var_len + 1] != '$' && str[idx + var_len + 1])
				var_len++;
			env_value = check_if_exist(str + idx + 1, envp);
			if (env_value)
				while (*env_value)
					(*new_str)[idx2++] = *env_value++;
			idx += var_len + 1;
		}
		else
			(*new_str)[idx2++] = str[idx++];
	}
}

// Return the value of the specified environment variable 
int	ft_replace_env(t_token *token, char **envp)
{
	int		final_size;
	char	*new_str;

	final_size = get_size(token->value, envp);
	if (final_size == -1)
		return (-1);
	new_str = ft_calloc(final_size + 1, sizeof(char));
	if (!new_str)
		return (-1);
	env_var_loop(token->value, &new_str, envp);
	free(token->value);
	token->value = new_str;
	return (0);
}
