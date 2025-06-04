/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:50:51 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/04 04:01:08 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_cmd(t_pipeline *pl, t_env *env)
{
	int		code;
	char	**ntab;
	char	**envp;
	int		builtin_type;

	ntab = rm_whitespace_tab(pl->cmd->argument);
	if (!ntab)
		return (perror("malloc"), 1);
	free_tab(pl->cmd->argument);
	pl->cmd->argument = ntab;
	builtin_type = is_builtin(ntab[0]);
	if (builtin_type > 0)
		return (exec_builtin(pl->cmd, env, builtin_type));
	code = ft_find_in_path(&pl->cmd->argument[0], env);
	if (code != 0)
		return (free_tab(ntab), code);
	code = check_exec(pl->cmd->argument[0]);
	if (code != 0)
		return (free_tab(ntab), code);
	envp = ft_env_to_tab(env);
	if (!envp)
		return (free_tab(ntab), perror("malloc"), 1);
	if (execve(ntab[0], ntab, envp) == -1)
		return (free_tab(envp), ft_print_errors("execve", 126), 126);
	return (1);
}

int	child_process(t_pipeline *pl, t_exec *exec)
{
	int			code;

	if (pl->id > 0)
		if (dup2(exec->pipe_tab[pl->id - 1][0], STDIN_FILENO) == -1)
			return (ft_print_errors("dup2", 0), 1);
	if (pl->id < exec->nb_child - 1)
		if (dup2(exec->pipe_tab[pl->id][1], STDOUT_FILENO) == -1)
			return (ft_print_errors("dup2", 0), 1);
	if (close_all_pipes(exec->pipe_tab, exec->nb_child - 1) != 0)
		return (ft_print_errors("pipes", 0), 1);
	code = exec_cmd(pl, exec->env);
	if (code != 0)
	{
		ft_print_errors("exec_cmd", code);
		return (code);
	}
	return (code);
}

int	wait_all_children(t_exec *exec)
{
	t_pipeline		*cur;
	int				code;
	int				status;

	cur = exec->top;
	code = 0;
	while (cur)
	{
		if (waitpid(cur->pid, &status, 0) < 0)
		{
			ft_print_errors("waitpid", 0);
			code = 1;
			cur = cur->next;
			continue ;
		}
		if (WIFSIGNALED(status))
			code = (128 + WTERMSIG(status));
		if (WIFEXITED(status))
			code = WEXITSTATUS(status);
		cur = cur->next;
	}
	return (code);
}

int	exec_main_loop(t_exec *exec)
{
	t_pipeline	*cur;
	int			code;

	code = 0;
	cur = exec->top;
	while (cur)
	{
		cur->pid = fork();
		if (cur->pid < 0)
			return (ft_print_errors("fork", 0), 1);
		if (cur->pid == 0)
		{
			code = child_process(cur, exec);
			exit(code);
		}
		cur = cur->next;
	}
	if (close_all_pipes(exec->pipe_tab, exec->nb_child - 1) != 0)
		return (1);
	code = wait_all_children(exec);
	return (code);
}

int	exec_main(t_parser *parse, t_env *env)
{
	t_exec	*exec;
	int		code;

	if (!parse || !parse->top || !parse->top->argument[0])
		return (1);
	if (parse->size == 1)
		return (exec_one(parse->top, env) != 0);
	exec = exec_init(parse->size, parse->top, env);
	if (!exec)
		return (1);
	code = exec_main_loop(exec);
	if (code != 0)
		return (exec_quit(parse, exec), 1);
	return (0);
}
