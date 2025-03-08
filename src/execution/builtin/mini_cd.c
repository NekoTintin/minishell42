/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:30:17 by unbuntu           #+#    #+#             */
/*   Updated: 2025/03/08 15:27:32 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

int	cd_tab_size(char **args)
{
	int		size;
	int		idx;

	size = 0;
	idx = 0;
	while (args[idx])
	{
		size++;
		idx++;
	}
	return (size);
}

int	mini_cd(char **args)
{
	char		*dir;
	int			size;

	size = cd_tab_size(args);
	if (size > 2)
		return (ft_putendl_fd("bash: cd: too many arguments", 2), 1);
	if (size == 1)
		dir = ".";
	else
		dir = args[1];
	if (chdir(dir) == -1)
	{
		ft_putchar_fd("bash: cd: ", 2);
		perror(dir);
		return (1);
	}
	return (0);
}
