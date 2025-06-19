/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:27:33 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/18 19:55:16 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	mini_export(char **argument, t_env *env)
{
	char	**tablo;
	char	**split;

	tablo = rm_whitespace_tab(argument);
	if (!tablo)
		return (EXIT_FAILURE);
	if (ft_strchr(tablo[1], '=') == NULL)
	{
		ft_putstr_fd("bash: export: `", 2);
		ft_putstr_fd(tablo[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free_tab(tablo);
		return (EXIT_FAILURE);
	}
	split = ft_split(tablo[1], '=');
	free_tab(tablo);
	if (split == NULL)
		return (EXIT_FAILURE);
	if (ft_add_to_env(env, split[0], split[1]) == 1)
		return (EXIT_FAILURE);
	free_tab(split);
	return (EXIT_SUCCESS);
}
