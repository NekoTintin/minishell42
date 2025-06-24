/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:36:27 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/24 23:02:02 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

int	ft_safe_atoi(const char *str, int *code)
{
	unsigned long long	ret;
	int					idx;
	int					j;
	int					sign;

	idx = 0;
	sign = 1;
	while ((str[idx] >= 9 && str[idx] <= 13) || str[idx] == ' ')
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
		if (str[idx++] == '-')
			sign = -1;
	j = idx;
	ret = 0;
	while (str[idx] >= '0' && str[idx] <= '9')
		ret = ret * 10 + (str[idx++] - '0');
	while ((str[idx] >= 9 && str[idx] <= 13) || str[idx] == ' ')
		idx++;
	if (str[idx] || idx - j > 20 || (sign == 1 && ret > LLG_MAX)
		|| (sign == -1 && (ret - 1) > LLG_MAX))
	{
		*code = 1;
		return (0);
	}
	return ((int)(sign * ret) % 256);
}

int	exit_check_errors(char **args, int *value)
{
	int		code;

	code = 0;
	*value = ft_safe_atoi(args[1], &code);
	if (code == 1)
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(" : numeric argument required\n", 2);
		return (2);
	}
	if (args[2])
	{
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	mini_exit_for_children(char **args)
{
	char	**tablo;
	int		ret;
	int		value;

	tablo = rm_whitespace_tab(args);
	if (!tablo)
	{
		perror("malloc");
		exit (1);
	}
	ft_putstr_fd("exit\n", 2);
	ret = 0;
	value = 0;
	if (tablo[1])
	{
		ret = exit_check_errors(tablo, &value);
		if (ret != 0)
		{
			free_tab(tablo);
			return (ret);
		}
	}
	free_tab(tablo);
	return (value);
}

int	mini_exit(char **args, t_parser *parse, t_exec *exec)
{
	char	**tablo;
	int		ret;
	int		value;

	tablo = rm_whitespace_tab(args);
	if (!tablo)
		return (perror("malloc"), 1);
	ft_putstr_fd("exit\n", 2);
	ret = 0;
	value = 0;
	if (tablo[1])
	{
		ret = exit_check_errors(tablo, &value);
		if (ret != 0)
		{
			free_tab(tablo);
			if (ret == 1)
				return (1);
			exec_quit(parse, exec);
			exit (ret);
		}
	}
	free_tab(tablo);
	exec_quit(parse, exec);
	exit(value);
}
