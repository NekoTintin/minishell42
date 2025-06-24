/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:27:33 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/24 20:39:49 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	mini_export_is_valid(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	mini_export_split(char *str, char **key, char **val)
{
	char		*splited;

	splited = ft_strchr(str, '=');
	if (splited)
	{
		*key = ft_substr(str, 0, splited - str);
		*val = ft_strdup(splited + 1);
	}
	else
	{
		*key = ft_strdup(str);
		*val = NULL;
	}
}

int	mini_export_foreach(char **tablo, char **key, char **val, int idx)
{
	if (!mini_export_is_valid(tablo[idx]))
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(tablo[idx], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		idx++;
		return (5);
	}
	mini_export_split(tablo[idx], key, val);
	if (!key)
		return (perror("malloc"), EXIT_FAILURE);
	return (0);
}

int	mini_export(char **argument, t_env *env)
{
	char	**tablo;
	int		idx;
	char	*key;
	char	*val;
	int		code;

	tablo = rm_whitespace_tab(argument);
	if (!tablo)
		return (perror("malloc"), EXIT_FAILURE);
	if (!tablo[1])
		return (0);
	idx = 1;
	while (tablo[idx])
	{
		code = mini_export_foreach(tablo, &key, &val, idx);
		if (code == 5)
		{
			idx++;
			continue ;
		}
		else if (code == 1)
			return (free_tab(tablo), EXIT_FAILURE);
		if (ft_add_to_env(env, key, val) != 0)
			ft_print_errors("export", 0);
		free(key);
		free(val);
		idx++;
	}
	return (free_tab(tablo), 0);
}
