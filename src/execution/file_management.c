/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:50:34 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/28 00:46:00 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	file_write(char *file, t_token_type type)
{
	int			fd;
	int			flags;

	if (type == REDIRECT_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (type == APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		return (-1);
	fd = open(file, flags, 0644);
	if (fd == -1)
		ft_print_errors(file);
	return (fd);
}

int	check_exec(char *exec)
{
	if (!exec || (access(exec, F_OK) == -1))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(exec, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	if (access(exec, X_OK) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(exec, 2);
		ft_putstr_fd(": permission denied\n", 2);
		return (126);
	}
	return (0);
}
