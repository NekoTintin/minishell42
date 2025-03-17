/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:36:17 by bchallat          #+#    #+#             */
/*   Updated: 2025/03/16 03:32:57 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

int	mini_env(char **envp)
{
	int		idx;

	idx = 0;
	while (envp[idx] != NULL)
	{
		printf("%s\n", envp[idx]);
		idx++;
	}
	return (0);
}
