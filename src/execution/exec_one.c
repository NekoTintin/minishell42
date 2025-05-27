/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:33:43 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/28 00:29:27 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_one_child_content(t_env *env)
{
	char	**new_envp;
	char	*path;

	new_envp = ft_env_to_tab(env);
	if (!new_envp)
		return (perror("malloc"), 1);
	path = ft_calloc(1, PATH_MAX);
}

int	exec_one_child(t_cmd *cmd, t_env *env)
{
	pid_t	child;
	int		status;
	int		error;

	child = fork();
	if (child < 0)
		return (ft_print_errors("fork"), 1);
	else if (child == 0)
	{
		
	}
	waitpid(child, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return WEXITSTATUS(status);
}

int	exec_one(t_cmd *cmd, t_env *env)
{
	int		code;
	int		builtin;

	builtin = is_builtin(cmd->argument[0]);
	if (is_builtin(cmd->argument[0]) < 0)
		return (ft_exec_builtin(cmd, env));
	else
		return (exec_one_child(cmd, env));
	return (-1);
}
