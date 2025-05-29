/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:08:48 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/28 21:25:55 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_loop(char *path, char *file, char **res)
{
	char		*slash_path;
	char		*full_path;

	slash_path = ft_strjoin(path, "/");
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

static char	**ft_get_splited_str(t_env *env)
{
	char		*path;
	char		**splited;

	path = ft_strdup(ft_env_get_value(env, "PATH"));
	if (!path)
		return (NULL);
	splited = ft_split(path, ':');
	if (!splited)
		return (free(path), NULL);
	return (splited);
}

static int	ft_absolute(char *file, char **res)
{
	if (access(file, X_OK) == 0)
	{
		*res = ft_strdup(file);
		if (!*res)
			return (1);
		return (0);
	}
	return (ft_print_errors(file, 126), 126);
}

int	ft_find_in_path(char *file, t_env *env, char **res)
{
	int			code;
	int			idx;
	char		**splited;

	if (!file || !env || !res)
		return (1);
	if (file[0] == '/')
		return (ft_absolute(file, res));
	splited = ft_get_splited_str(env);
	if (!splited)
		return (1);
	idx = 0;
	while (splited[idx])
	{
		code = find_loop(splited[idx], file, res);
		if (code != 2)
			return (free_tab(splited), code);
		idx++;
	}
	ft_print_errors(file, 127);
	return (free_tab(splited), 127);
}
