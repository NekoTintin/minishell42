/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_test_mini_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:55:18 by bchallat          #+#    #+#             */
/*   Updated: 2025/03/18 13:55:37 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "testeur.h"

void	print_env_array(char **var_env)
{
	int	index;

	index = 0;
	while (var_env[index] !=  NULL)
	{
		printf("export %s\n", var_env[index]);
		index++;
	}
}

char	**cp_array_env(char **envp, int length)
{
	char	**var_env;
	int	index;

	var_env = (char **)ft_calloc(ft_arrlen(envp) + 1 + length, sizeof(char *));
	if (var_env == NULL)
     		return (NULL);
	index = 0;
	while (envp != NULL && envp[index] != NULL)
	{
		var_env[index] = ft_strdup(envp[index]);
		if (var_env[index] == NULL)
			return (NULL);
		index++;
	}
	return (var_env);
}

int	ft_arrlen(char **array)
{
	int	index;

	index = 0;
	while (array[index] != NULL)
		index++;
	return (index);
}
