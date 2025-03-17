/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:36:37 by bchallat          #+#    #+#             */
/*   Updated: 2025/03/17 04:24:09 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

void	export_print(char **envp)
{
	int		idx;

	idx = 0;
	while (envp[idx] != NULL)
	{
		printf("declare -x %s\n", envp[idx]);
		idx++;
	}
}

int	mini_export(char **args, char **envp)
{
	if (args[1] == NULL)
		return (export_print(envp), 0);
}
