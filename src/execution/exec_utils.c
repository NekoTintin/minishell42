/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:42:31 by qupollet          #+#    #+#             */
/*   Updated: 2025/03/08 19:04:37 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exec_builtin(t_cmd *cmd, char **envp)
{
	int	builtin_type;

	builtin_type = ft_is_builtin(cmd->argument[0]);
	if (builtin_type == 2)
		return (mini_cd(cmd->argument));
	if (builtin_type == 3)
		return (mini_pwd());
	return (127);
}

int	ft_is_builtin(const char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0 && (ft_strlen(str) == 4))
		return (1);
	else if (ft_strncmp(str, "cd", 2) == 0 && (ft_strlen(str) == 2))
		return (2);
	else if (ft_strncmp(str, "pwd", 3) == 0 && (ft_strlen(str) == 3))
		return (3);
	else if (ft_strncmp(str, "export", 6) == 0 && (ft_strlen(str) == 6))
		return (4);
	else if (ft_strncmp(str, "unset", 5) == 0 && (ft_strlen(str) == 5))
		return (5);
	else if (ft_strncmp(str, "env", 3) == 0 && (ft_strlen(str) == 3))
		return (6);
	else if (ft_strncmp(str, "exit", 4) == 0 && (ft_strlen(str) == 4))
		return (7);
	return (-1);
}
