/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 23:57:18 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/17 20:57:17 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_builtin_solo(t_cmd *cmd, t_parser *parse, t_exec *exec, int type)
{
	int		fd_in;
	int		fd_out;
	int		code;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	if (fd_in < 0 || fd_out < 0)
		return (ft_print_errors("bash: dup2", 0), 1);
	if (ft_redirects(cmd, fd_in, fd_out, exec->env) != 0)
	{
		exec_restore_stdfd(fd_in, fd_out);
		return (1);
	}
	code = exec_builtin(cmd, parse, exec, type);
	exec_restore_stdfd(fd_in, fd_out);
	return (code);
}

int	exec_builtin_pipeline(t_cmd *cmd, t_parser *parse, t_exec *exec, int type)
{
	int		code;

	code = exec_builtin(cmd, parse, exec, type);
	free_all_parser(parse);
	free_exec(exec);
	clear_history();
	return (code);
}

int	is_builtin(char *cmd)
{
	if (!cmd || cmd[0] == '\0')
		return (-1);
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

int	exec_builtin(t_cmd *cmd, t_parser *parse, t_exec *exec, int builtin_code)
{
	if (!cmd || !cmd->argument || !cmd->argument[0] || !exec)
		return (127);
	if (builtin_code == 1)
		return (mini_echo(cmd->argument, exec->env), 0);
	else if (builtin_code == 2)
		return (mini_cd(cmd->argument, exec->env));
	else if (builtin_code == 3)
		return (mini_pwd(), 0);
	else if (builtin_code == 4)
		return (mini_export(cmd->argument, exec->env));
	else if (builtin_code == 5)
		return (mini_unset(cmd->argument, exec->env));
	else if (builtin_code == 6)
		return (mini_env(exec->env));
	else if (builtin_code == 7)
		return (mini_exit(cmd->argument, parse, exec));
	return (127);
}
