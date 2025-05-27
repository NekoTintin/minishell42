/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:30:38 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/27 19:30:24 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_errors(char *src)
{
	ft_putstr_fd("bash: ", 2);
	perror(src);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0 && (ft_strlen(cmd) == 4))
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0 && (ft_strlen(cmd) == 2))
		return (2);
	else if (ft_strncmp(cmd, "pwd", 3) == 0 && (ft_strlen(cmd) == 3))
		return (3);
	else if (ft_strncmp(cmd, "export", 6) == 0 && (ft_strlen(cmd) == 6))
		return (4);
	else if (ft_strncmp(cmd, "unset", 5) == 0 && (ft_strlen(cmd) == 5))
		return (5);
	else if (ft_strncmp(cmd, "env", 3) == 0 && (ft_strlen(cmd) == 3))
		return (6);
	else if (ft_strncmp(cmd, "exit", 4) == 0 && (ft_strlen(cmd) == 4))
		return (7);
	return (-1);
}
