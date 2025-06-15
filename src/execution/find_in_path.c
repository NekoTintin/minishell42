/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:08:48 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/11 16:52:41 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_loop(char *path, char **file)
{
	char		*slash_path;
	char		*full_path;

	slash_path = ft_strjoin(path, "/");
	if (!slash_path)
		return (1);
	full_path = ft_strjoin(slash_path, *file);
	free(slash_path);
	if (!full_path)
		return (1);
	if (access(full_path, X_OK) == 0)
	{
		free(*file);
		*file = ft_strdup(full_path);
		free(full_path);
		if (!*file)
			return (1);
		return (0);
	}
	free(full_path);
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
	free(path);
	if (!splited)
		return (NULL);
	return (splited);
}

static int	ft_absolute(char **file)
{
	if (access(*file, F_OK) == -1)
		return (ft_print_errors(*file, 127), 127);
	if (access(*file, X_OK) == -1)
		return (ft_print_errors(*file, 126), 126);
	return (0);
}

int	ft_find_in_path(char **file, t_env *env)
{
	int			code;
	int			idx;
	char		**splited;

	if (!file || !env)
		return (1);
	if (ft_strchr(file[0], '/'))
		return (ft_absolute(file));
	splited = ft_get_splited_str(env);
	if (!splited)
		return (1);
	idx = 0;
	while (splited[idx])
	{
		code = find_loop(splited[idx], file);
		if (code != 2)
			return (free_tab(splited), code);
		idx++;
	}
	ft_putstr_fd(*file, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (free_tab(splited), 127);
}
