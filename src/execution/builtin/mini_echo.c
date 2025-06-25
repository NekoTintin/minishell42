/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:36:05 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/25 14:28:49 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

int	no_newline(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (0);
	i = 2;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

static void	mini_echo_loop(int *first, int *idx, char **ntab)
{
	if (*first > 0)
		write(1, " ", 1);
	ft_putstr_fd(ntab[*idx], 1);
	*idx += 1;
	*first += 1;
}

void	mini_echo(char **args)
{
	char		**ntab;
	int			nl;
	int			idx;
	int			first;

	ntab = rm_whitespace_tab(args + 1);
	if (!ntab || !*ntab)
	{
		free(ntab);
		return ;
	}
	nl = no_newline(ntab[0]);
	idx = 0;
	if (nl)
		idx++;
	first = 0;
	while (ntab[idx])
		mini_echo_loop(&first, &idx, ntab);
	if (nl == 0)
		write(1, "\n", 1);
	free_tab(ntab);
}
