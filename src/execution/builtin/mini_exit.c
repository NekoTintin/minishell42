/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:36:27 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/20 14:34:19 by qupollet         ###   ########.fr       */
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

int	exit_check_errors(char **args)
{
	if (exit_contain_char(args[1]) == 1)
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(" : numeric argument required\n", 2);
		return (255);
	}
	if (args[2])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	mini_exit(char **args, t_parser *parse, t_exec *exec)
{
	char	**tablo;
	int		ret;

	tablo = rm_whitespace_tab(args);
	if (!tablo)
		return (perror("malloc"), 1);
	ft_putstr_fd("exit\n", 1);
	if (args[1])
	{
		ret = exit_check_errors(tablo);
		free_tab(tablo);
		if (ret != 0)
			return (ret);
		ret = atoi(args[1]) % 256;
		exec_quit(parse, exec);
		exit(ret);
	}
	free_tab(tablo);
	exec_quit(parse, exec);
	exit(0);
}
