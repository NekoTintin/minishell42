/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:36:27 by bchallat          #+#    #+#             */
/*   Updated: 2025/03/17 04:29:07 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

int	exit_contain_char(char *arg)
{
	int		idx;

	idx = 0;
	while (arg[idx])
	{
		if (arg[idx] < '0' || arg[idx] > '9')
			return (1);
		idx++;
	}
	return (0);
}

// DON'T FORGET TO FREE ALL THE STRUCTURES ALLOCATED IN THE MAIN LOOP!!!
// ADD THIS BEFORE THE EXITS
int	mini_exit(char **args)
{
	if (args[1])
	{
		if (exit_contain_char(args[1]) == 1)
		{
			ft_putstr_fd("bash: exit", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (1);
		}
		if (args[2])
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			return (1);
		}
		exit(atoi(args[1]));
	}
	exit(0);
}
