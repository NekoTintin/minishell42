/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:27:33 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/24 17:29:10 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_tablo(char **tablo)
{
	int	i;

	i = 0;
	while (tablo[i])
	{
		ft_printf("elem %d ", i);
		ft_putstr_fd(tablo[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

int	mini_export_is_valid(const char *str)
{
	int	i;

	if (!str || !ft_isalpha(str[0]) && str[0] != "_")
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

int	mini_export_split(char *str, t_env *env)
{
	char		*splited;
	char		*key;
	char		*value;

	splited = ft_strchr(str, '=');
	if (splited)
	{
		key = ft_substr(str, 0, splited - str);
		value = ft_strdup(splited + 1);
	}
	else
	{
		key = ft_strdup(str);
		value = NULL;
	}
	if (ft_add_to_env(env, key, value) == 1)
	{
		free(key);
		free(value);
		return (1);
	}
	return (0);
}

int	mini_export(char **argument, t_env *env)
{
	char	**tablo;
	int		idx;

	tablo = rm_whitespace_tab(argument);
	if (!tablo)
		return (EXIT_FAILURE);
	if (!tablo[1])
		return (0);
	idx = 1;
	while (tablo[idx])
	{
		if (!mini_export_is_valid(tablo[idx]))
		{
			ft_putstr_fd("bash: export: `", 2);
			ft_putstr_fd(tablo[1], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
			mini_export_split(tablo[idx], env);
		idx++;
	}
}
