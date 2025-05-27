/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:30:38 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/28 01:11:18 by qupollet         ###   ########.fr       */
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

int	exec_builtin(t_cmd *cmd, t_env *env, int builtin_code)
{
	if (builtin_code == 1)
		return (mini_echo(cmd->argument));
	else if (builtin_code == 2)
		return (mini_cd(cmd->argument, env));
	else if (builtin_code == 3)
		return (mini_pwd());
	else if (builtin_code == 4)
		return (mini_env(env));
	return (127);
}
