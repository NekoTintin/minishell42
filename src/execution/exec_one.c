/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:33:43 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/18 20:01:41 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_one_child_content(t_cmd *cmd, t_env *env, char **envp)
{
	int		code;
	char	**ntab;

	ntab = rm_whitespace_tab(cmd->argument);
	if (!ntab)
		return (perror("malloc"), 1);
	free_tab(cmd->argument);
	cmd->argument = ntab;
	code = ft_find_in_path(&cmd->argument[0], env);
	if (code != 0)
		return (free_tab(ntab), code);
	code = check_exec(cmd->argument[0]);
	if (code != 0)
		return (free_tab(ntab), code);
	if (execve(ntab[0], ntab, envp) == -1)
		return (free_tab(ntab), ft_print_errors("execve", 126), 126);
	return (1);
}

int	exec_one_child(t_cmd *cmd, t_env *env)
{
	pid_t	child;
	int		status;
	char	**envp;

	if (ft_find_in_path(&cmd->argument[0], env) != 0)
		return (127);
	envp = ft_env_to_tab(env);
	if (!envp)
		return (perror("malloc"), 1);
	child = fork();
	if (child < 0)
		return (free_tab(envp), ft_print_errors("fork", 0), 1);
	else if (child == 0)
	{
		if (ft_redirects(cmd, STDIN_FILENO, STDOUT_FILENO, env) != 0)
			return (1);
		exit(ft_one_child_content(cmd, env, envp));
	}
	waitpid(child, &status, 0);
	free_tab(envp);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	exec_one(t_cmd *cmd, t_parser *parse, t_exec *exec)
{
	int		builtin;
	int		code;

	builtin = is_builtin(cmd->argument[0]);
	if (builtin > 0)
		return (exec_builtin_solo(cmd, parse, exec, builtin));
	else
		return (exec_one_child(cmd, exec->env));
	free_exec(exec);
	return (code);
}
