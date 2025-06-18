/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:36:05 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/18 20:29:51 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

int	skip_spaces(char **tablo)
{
	int	i;
	int	j;

	i = 0;
	while (tablo[i])
	{
		j = 0;
		while (tablo[i][j] == ' ')
			j++;
		if (tablo[i][j] != '\0')
			break ;
		i++;
	}
	return (i);
}

int	echo_check_args(char **arg)
{
	int		i;
	int		j;

	i = skip_spaces(arg);
	if (!arg[i])
		return (1);
	if (arg[i][0] != '-' || arg[i][1] != 'n')
		return (1);
	j = 2;
	while (arg[i][j] == 'n')
		j++;
	if (arg[i][j] != '\0')
		return (1);
	return (0);
}

void	mini_echo(char **args, t_env *env)
{
	int		idx;
	int		new_line;

	if (!args[1])
		return ;
	new_line = echo_check_args(args + 1);
	idx = 1;
	if (new_line == 0)
		idx = skip_spaces(args) + 1;
	while (args[idx])
	{
		if (args[idx][0] == '$')
			ft_putstr_fd(ft_env_get_value(env, &args[idx][1]), 1);
		else
			ft_putstr_fd(args[idx], 1);
		idx++;
	}
	if (new_line == 1)
		ft_putstr_fd("\n", 1);
}
