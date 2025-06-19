/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:37:00 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/18 20:05:42 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

int	mini_unset(char **args, t_env *env)
{
	char		**tablo;

	tablo = rm_whitespace_tab(args);
	if (!tablo)
		return (EXIT_FAILURE);
	if (env_remove(&env, tablo[1]) == 1)
	{
		free_tab(tablo);
		return (EXIT_FAILURE);
	}
	free_tab(tablo);
	return (EXIT_SUCCESS);
}
