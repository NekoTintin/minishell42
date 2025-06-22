/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:33:43 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/22 19:49:02 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fr(t_exec *exec)
{
	ft_free_env(exec->env);
	free(exec->mini);
	free_exec(exec);
	clear_history();
}

int	ft_one_child_content(t_cmd *cmd, t_exec *exec)
{
	int		code;
	char	**ntab;
	char	**envp;

	envp = ft_env_to_tab(exec->env);
	if (!envp)
		return (fr(exec), perror("malloc"), 1);
	ntab = rm_whitespace_tab(cmd->argument);
	if (!ntab)
		return (fr(exec), perror("malloc"), 1);
	free_tab(cmd->argument);
	cmd->argument = ntab;
	code = ft_find_in_path(&cmd->argument[0], exec->env);
	if (code != 0)
		return (fr(exec), free_tab(envp), free_tab(ntab), code);
	code = check_exec(cmd->argument[0]);
	if (code != 0)
		return (fr(exec), free_tab(envp), free_tab(ntab), code);
	if (execve(ntab[0], ntab, envp) == -1)
	{
		free_tab(envp);
		return (fr(exec), free_tab(ntab), ft_print_errors("execve", 126), 126);
	}
	fr(exec);
	return (1);
}

int	exec_one_child(t_pipeline *pl, t_exec *exec)
{
	pid_t	child;
	int		status;

	if (ft_find_in_path(&pl->cmd->argument[0], exec->env) != 0)
		return (127);
	child = fork();
	if (child < 0)
		return (ft_print_errors("fork", 0), 1);
	else if (child == 0)
	{
		sig_setup_defaut();
		if (ft_redirects(pl, STDIN_FILENO, STDOUT_FILENO) != 0)
			exit (1);
		exit(ft_one_child_content(pl->cmd, exec));
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(child, &status, 0);
		sig_setup_mini();
	}
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	exec_pipeline_solo(t_cmd *cmd, t_exec *exec)
{
	exec->top = ft_create_pipeline(1, cmd, exec);
	if (!exec->top)
		return (ft_print_errors("malloc", 0), 1);
	if (exec_prepare_heredoc(exec) != 0)
		return (1);
	return (0);
}

int	exec_one(t_cmd *cmd, t_parser *parse, t_exec *exec)
{
	int		builtin;

	if (exec_pipeline_solo(cmd, exec) != 0)
		return (1);
	builtin = is_builtin(cmd->argument[0]);
	if (builtin > 0)
		return (exec_builtin_solo(exec->top, parse, exec, builtin));
	else
		return (exec_one_child(exec->top, exec));
	return (0);
}
