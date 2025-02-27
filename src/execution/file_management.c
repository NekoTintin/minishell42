/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 03:23:49 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/24 15:44:44 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_checkfile(char *file, int append)
{
	int		fd;

	if (access(file, F_OK) == -1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0744);
		if (fd == -1)
			return (-1);
	}
	else if (access(file, W_OK))
		return (-1);
	else
	{
		if (append == 0)
			fd = open(file, O_WRONLY | O_TRUNC);
		else if (append == 1)
			fd = open(file, O_WRONLY | O_APPEND);
		if (fd == -1)
			return (-1);
	}
	return (fd);
}

int	ft_checkprog(char *prog)
{
	if (!prog)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(prog, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	if (access(prog, F_OK) != 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(prog, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	if (access(prog, X_OK) != 0)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(prog, 2);
		ft_putstr_fd(": permission denied\n", 2);
		return (126);
	}
	return (0);
}
