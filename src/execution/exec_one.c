/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:33:43 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/23 17:25:41 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fr(t_cmd *cmd, t_exec *exec)
{
	t_redirect	*red;

	ft_free_env(exec->env);
	free(exec->mini);
	free_exec(exec);
	clear_history();
	red = cmd->redirect;
	while (red)
	{
		if (red->heredoc)
		{
			if (unlink(red->heredoc) == -1)
				ft_print_errors(red->heredoc, 126);
			free(red->heredoc);
		}
	}
}

int	ft_one_child_content(t_cmd *cmd, t_exec *exec)
{
	int		code;
	char	**ntab;
	char	**envp;

	envp = ft_env_to_tab(exec->env);
	if (!envp)
		return (fr(cmd, exec), perror("malloc"), 1);
	ntab = rm_whitespace_tab(cmd->argument);
	if (!ntab)
		return (fr(cmd, exec), perror("malloc"), 1);
	free_tab(cmd->argument);
	cmd->argument = ntab;
	code = ft_find_in_path(&cmd->argument[0], exec->env);
	if (code != 0)
		return (fr(cmd, exec), free_tab(envp), free_tab(ntab), code);
	code = check_exec(cmd->argument[0]);
	if (code != 0)
		return (fr(cmd, exec), free_tab(envp), free_tab(ntab), code);
	if (execve(ntab[0], ntab, envp) == -1)
	{
		ft_print_errors("execve", 126);
		return (fr(cmd, exec), free_tab(ntab), free_tab(envp), 126);
	}
	fr(cmd, exec);
	return (1);
}

int	exec_one_child(t_cmd *cmd, t_exec *exec)
{
	pid_t	child;
	int		status;

	if (ft_find_in_path(&cmd->argument[0], exec->env) != 0)
		return (127);
	child = fork();
	if (child < 0)
		return (ft_print_errors("fork", 0), 1);
	else if (child == 0)
	{
		sig_setup_defaut();
		if (ft_redirects(cmd, STDIN_FILENO, STDOUT_FILENO) != 0)
			exit (1);
		exit(ft_one_child_content(cmd, exec));
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

int	exec_one(t_cmd *cmd, t_parser *parse, t_exec *exec)
{
	int		builtin;
	int		code;

	code = exec_heredoc(cmd);
	if (code != 0)
		return (code);
	builtin = is_builtin(cmd->argument[0]);
	if (builtin > 0)
		return (exec_builtin_solo(cmd, parse, exec, builtin));
	else
		return (exec_one_child(cmd, exec));
	return (0);
}
