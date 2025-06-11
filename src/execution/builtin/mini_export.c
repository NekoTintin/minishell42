//* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:04:02 by bchallat          #+#    #+#             */
/*   Updated: 2025/03/18 13:55:55 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../../includes/minishell.h"

int	mini_export(char **argument, t_env *env)
{
	char	**split;

	if ((split = ft_split(argument[2], '=')) == NULL)
		return (EXIT_FAILURE);
	if (ft_add_to_env(env, split[0], split[1]) == 1)
		return (EXIT_FAILURE);
	free_tab(split);	
	return (EXIT_SUCCESS);
}

