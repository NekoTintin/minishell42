/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:37:00 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/11 18:28:00 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

int	mini_unset(char **args, t_env *env)
{
	if (env_remove(&env, args[2]) == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
