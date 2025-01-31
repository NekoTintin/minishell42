/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:32:21 by qupollet          #+#    #+#             */
/*   Updated: 2025/01/22 18:02:02 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
