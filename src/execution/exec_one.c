/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:33:43 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/27 18:19:51 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	fr(t_exec *exec)
{
	ft_free_env(exec->env);
	free_all_parser(exec->mini->parse);
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
	code = check_exec(cmd->argument[0]);
	if (code != 0)
		return (fr(exec), free_tab(envp), free_tab(ntab), code);
	if (execve(ntab[0], ntab, envp) == -1)
	{
		ft_print_errors("execve", 126);
		return (fr(exec), free_tab(envp), 126);
	}
	fr(exec);
	return (1);
}

void	exec_one_content_child(t_cmd *cmd, t_exec *exec)
{
	sig_setup_defaut();
	if (ft_redirects(cmd, STDIN_FILENO, STDOUT_FILENO) != 0)
	{
		fr(exec);
		exit(1);
	}
	exit(ft_one_child_content(cmd, exec));
}

int	exec_one_child(t_cmd *cmd, t_exec *exec)
{
	pid_t	child;
	int		status;

	status = 0;
	if (ft_find_in_path(&cmd->argument[0], exec->env) != 0)
		return (127);
	child = fork();
	if (child < 0)
		return (ft_print_errors("fork", 0), 1);
	else if (child == 0)
		exec_one_content_child(cmd, exec);
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

	code = redir_prepare(parse, exec);
	if (code != 0)
		return (code);
	builtin = is_builtin(cmd->argument[0]);
	if (builtin > 0)
	{
		code = exec_builtin_solo(cmd, parse, exec, builtin);
		free_heredoc(cmd);
		return (code);
	}
	else
	{
		code = exec_one_child(cmd, exec);
		if (code == 130)
			write(2, "\n", 1);
		if (code == 131)
			write(2, "Quit(core dumped)\n", 18);
		free_heredoc(cmd);
		return (code);
	}
	return (0);
}
