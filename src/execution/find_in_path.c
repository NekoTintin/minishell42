/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:08:48 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/28 00:36:51 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_loop(t_env *cur, char *file, char **res)
{
	char		*slash_path;
	char		*full_path;

	if (!cur->value)
		return (2);
	slash_path = ft_strjoin(cur->value, "/");
	if (!slash_path)
		return (1);
	full_path = ft_strjoin(slash_path, file);
	free(slash_path);
	if (!full_path)
		return (1);
	if (access(full_path, X_OK) == 0)
	{
		*res = ft_strdup(full_path);
		free(full_path);
		if (!*res)
			return (1);
		return (0);
	}
	return (2);
}

int	ft_find_in_path(char *file, t_env *env, char **res)
{
	t_env		*cur;
	int			code;

	if (!file || !env || !res)
		return (1);
	if (file[0] == '/')
	{
		if (access(file, X_OK) == 0)
		{
			*res = ft_strdup(file);
			if (!*res)
				return (1);
			return (0);
		}
		return (126);
	}
	cur = env;
	while (cur)
	{
		code = find_loop(cur, file, res);
		if (code != 2)
			return (code);
		cur = cur->next;
	}
	return (127);
}
