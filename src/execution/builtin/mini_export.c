/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:27:33 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/11 19:20:40 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// Now fully normed !
int	mini_export(char **argument, t_env *env)
{
	char	**split;

	split = ft_split(argument[2], '=');
	if (split == NULL)
		return (EXIT_FAILURE);
	if (ft_add_to_env(env, split[0], split[1]) == 1)
		return (EXIT_FAILURE);
	free_tab(split);
	return (EXIT_SUCCESS);
}
