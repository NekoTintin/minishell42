/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:36:05 by bchallat          #+#    #+#             */
/*   Updated: 2025/05/28 19:01:28 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

int	echo_check_args(char *arg)
{
	int		idx;

	if (!arg)
		return (1);
	while (*arg == ' ')
		arg++;
	if (arg[0] == '-' && arg[1] == 'n')
	{
		idx = 1;
		while (arg[idx] == 'n')
			idx++;
		if (arg[idx] == '\0')
			return (0);
	}
	return (1);
}

void	mini_echo(char **args)
{
	int		idx;
	int		new_line;

	new_line = echo_check_args(args[1]);
	idx = 1;
	if (args[1] && new_line == 0)
		idx++;
	while (args[idx])
	{
		ft_putstr_fd(args[idx], 1);
		idx++;
		if (args[idx])
			printf(" ");
	}
	if (new_line == 1)
		ft_putstr_fd("\n", 1);
}
