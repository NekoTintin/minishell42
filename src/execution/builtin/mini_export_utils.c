/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 17:23:46 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/29 14:05:36 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	free_tab_export(char **tablo, int idx)
{
	if (!tablo)
		return ;
	while (idx >= 0)
	{
		free(tablo[idx]);
		idx--;
	}
	free(tablo);
	return ;
}

char	**copy_tab(char **src)
{
	int		i;
	char	**copy;

	if (!src)
		return (NULL);
	i = 0;
	while (src[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (src[i])
	{
		copy[i] = ft_strdup(src[i]);
		if (!copy[i])
		{
			free_tab_export(copy, i);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	**m_exp_tab(char **args)
{
	char	*join;
	char	**array;

	join = NULL;
	array = NULL;
	if (args[1][ft_strlen(args[1]) - 1] != '='
		|| args[2] == NULL)
		return (copy_tab(args));
	join = ft_strjoin(args[1], args[2]);
	if (join == NULL)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * 3);
	if (array == NULL)
		return (free(join), NULL);
	array[0] = ft_strdup(args[0]);
	if (array[0] == NULL)
		return (free(array), free(join), NULL);
	array[1] = ft_strdup(join);
	if (array[1] == NULL)
		return (free(array), free(join), NULL);
	array[2] = NULL;
	return (free(join), array);
}
