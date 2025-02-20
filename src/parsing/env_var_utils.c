/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 00:55:28 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/20 01:28:24 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../includes/minishell.h"

int	ft_custom_strlen(char *str)
{
	int		idx;
	int		size;

	idx = 0;
	size = 0;
	while (str[idx] && str[idx] != ' ' && str[idx] != '$')
	{
		idx++;
		size++;
	}
	return (size);
}

char	*get_env_value(char *str, char **envp)
{
	int		len;
	char	*var_name;
	char	*env_value;

	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '$')
		len++;
	var_name = ft_substr(str, 0, len);
	if (!var_name)
		return (NULL);
	env_value = check_if_exist(var_name, envp);
	free(var_name);
	return (env_value);
}
