/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:40:42 by qupollet          #+#    #+#             */
/*   Updated: 2025/03/08 17:22:16 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Find the first value that's start with PATH= in envp
char	*ft_find_path(char **envp)
{
	int		idx;

	idx = 0;
	while (envp[idx] != NULL)
	{
		if (ft_strncmp(envp[idx], "PATH=", 5) == 0)
			return (envp[idx]);
		idx++;
	}
	return (NULL);
}

// Transform PATH string var into a tab
char	**ft_split_envp(char *path)
{
	char	*new_path;
	char	**path_tab;

	new_path = ft_substr(path, 5, ft_strlen(path));
	if (!new_path)
		return (NULL);
	path_tab = ft_split(new_path, ':');
	free(new_path);
	if (!path_tab)
		return (NULL);
	return (path_tab);
}

// Join for each string in path_tab with prog and test 
int	ft_test_each_str(char *filename, char **splited_path, char **result)
{
	int		idx;
	char	*path_with_slash;
	char	*full_path;

	idx = -1;
	while (splited_path[++idx])
	{
		path_with_slash = ft_strjoin(splited_path[idx], "/");
		if (!path_with_slash)
			return (1);
		full_path = ft_strjoin(path_with_slash, filename);
		free(path_with_slash);
		if (!full_path)
			return (1);
		if (access(full_path, X_OK) == 0)
		{
			*result = ft_strdup(full_path);
			free(full_path);
			if (!*result)
				return (1);
			return (0);
		}
		free(full_path);
	}
	return (127);
}

int	ft_find_in_envp(char **filename, char **envp)
{
	char	*path_envp;
	char	**tab_path;
	char	*result;
	int		error_code;

	if (filename[0][0] == '/')
		return (0);
	path_envp = ft_find_path(envp);
	if (!path_envp)
		return (127);
	tab_path = ft_split_envp(path_envp);
	if (!tab_path)
		return (1);
	error_code = ft_test_each_str(*filename, tab_path, &result);
	if (error_code != 0)
		return (ft_freetab(tab_path), error_code);
	free(*filename);
	*filename = result;
	ft_freetab(tab_path);
	return (0);
}
