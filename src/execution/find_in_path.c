/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:08:48 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/27 23:28:01 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_find_in_path(char *file, t_env *env, char **res)
{
	t_env		*cur;
	char		*slash_path;
	char		*full_path;

	if (file[0] == '/')
		return (0);
	cur = env;
	while (cur)
	{
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
			if (!*res)
				return (free(full_path), 1);
			return (free(full_path), 0);
		}
	}
	return (127);
}
