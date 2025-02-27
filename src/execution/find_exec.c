/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:43:51 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/21 18:53:51 by qupollet         ###   ########.fr       */
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
char	**ft_transform_in_tab(char *path)
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
char	*ft_test_for_each(char *prog, char **path_tab)
{
	int		idx;
	char	*tmp;
	char	*tmp2;

	idx = 0;
	while (path_tab[idx] != NULL)
	{
		tmp = ft_strjoin(path_tab[idx], "/");
		if (!tmp)
			return (NULL);
		tmp2 = ft_strjoin(tmp, prog);
		free(tmp);
		if (!tmp2)
			return (NULL);
		if (access(tmp2, X_OK) == 0)
			return (tmp2);
		free(tmp2);
		idx++;
	}
	return (NULL);
}

// Clean prog string from invalid char
char	*ft_get_clean_prog(char	*prog)
{
	char	*fstr;
	int		start;
	int		end;

	if (!prog || prog[0] == '\0')
		return (NULL);
	start = 0;
	while ((prog[start] >= 9 && prog[start] <= 13) || prog[start] == ' ')
		start++;
	if (prog[start] == '\0')
		return (NULL);
	end = start;
	while (!(prog[end] >= 9 && prog[end] <= 13)
		&& prog[end] != ' ' && prog[end] != '\0')
		end++;
	fstr = ft_substr(prog, start, end - start);
	if (!fstr)
		return (NULL);
	return (fstr);
}

// Check if prog is already a path otherwise return program path
char	*ft_find_exec_in_envp(char *prog, char **envp)
{
	char		*path;
	char		**path_tab;
	char		*complete_path;
	char		*clean_prog;

	if (ft_is_absolute(prog))
	{
		complete_path = ft_strdup(prog);
		if (!complete_path)
			return (NULL);
		return (complete_path);
	}
	path = ft_find_path(envp);
	if (path == NULL)
		return (NULL);
	path_tab = ft_transform_in_tab(path);
	if (!path_tab)
		return (NULL);
	clean_prog = ft_get_clean_prog(prog);
	if (!clean_prog)
		return (NULL);
	complete_path = ft_test_for_each(clean_prog, path_tab);
	ft_freetab(path_tab);
	free(clean_prog);
	return (complete_path);
}
