/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:33:43 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/28 00:56:51 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_one_child_content(t_cmd *cmd, t_env *env, char **new_envp, char *path)
{
	int		code;

	code = ft_find_in_path(cmd->argument[0], env, &path);
	if (code != 0)
		exit (code);
	code = check_exec(path);
	if (code != 0)
		exit(code);
	free(cmd->argument[0]);
	cmd->argument[0] = path;
	if (exevce(cmd->argument[0], cmd->argument, new_envp) == -1)
	{
		ft_print_errors("execve");
		exit(1);
	}
	exit (1);
}

int	exec_one_child(t_cmd *cmd, t_env *env)
{
	pid_t	child;
	int		status;
	char	*path;
	char	**new_envp;

	new_envp = ft_env_to_tab(env);
	if (!new_envp)
		return (perror("malloc"), 1);
	path = ft_calloc(1, PATH_MAX);
	if (!path)
		return (free_tab(new_envp), perror("malloc"), 1);
	child = fork();
	if (child < 0)
		return (free_tab(new_envp), free(path), ft_print_errors("fork"), 1);
	else if (child == 0)
	{
		if (ft_one_child_content(cmd, env, new_envp, path) == -1)
			exit(1);
	}
	waitpid(child, &status, 0);
	free_tab(new_envp);
	free(path);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	exec_one(t_cmd *cmd, t_env *env)
{
	int		code;
	int		builtin;

	builtin = is_builtin(cmd->argument[0]);
	if (builtin < 0)
		return (ft_exec_builtin(cmd, env));
	else
		return (exec_one_child(cmd, env));
	return (-1);
}
