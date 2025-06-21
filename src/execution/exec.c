/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:50:51 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/20 17:58:51 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_cmd(t_pipeline *pl, t_parser *parse, t_exec *exec)
{
	int		code;
	char	**ntab;
	char	**envp;
	int		builtin_type;

	builtin_type = is_builtin(pl->cmd->argument[0]);
	if (builtin_type > 0)
		return (exec_builtin_pipeline(pl->cmd, parse, exec, builtin_type));
	ntab = rm_whitespace_tab(pl->cmd->argument);
	if (!ntab)
		return (perror("malloc"), 1);
	free_tab(pl->cmd->argument);
	pl->cmd->argument = ntab;
	code = ft_find_in_path(&pl->cmd->argument[0], exec->env);
	if (code != 0)
		return (free_tab(ntab), code);
	code = check_exec(pl->cmd->argument[0]);
	if (code != 0)
		return (free_tab(ntab), code);
	envp = ft_env_to_tab(exec->env);
	if (!envp)
		return (free_tab(ntab), perror("malloc"), 1);
	if (execve(ntab[0], ntab, envp) == -1)
		return (free_tab(envp), ft_print_errors("execve", 126), 126);
	return (1);
}

int	child_process(t_pipeline *pl, t_exec *exec, t_parser *parse)
{
	int			code;

	if (pl->id > 0)
		if (dup2(exec->pipe_tab[pl->id - 1][0], STDIN_FILENO) == -1)
			return (ft_print_errors("dup2", 0), 1);
	if (pl->id < exec->nb_child - 1)
		if (dup2(exec->pipe_tab[pl->id][1], STDOUT_FILENO) == -1)
			return (ft_print_errors("dup2", 0), 1);
	if (ft_redirects(pl->cmd, STDIN_FILENO, STDOUT_FILENO, exec) != 0)
		exit(1);
	if (close_all_pipes(exec->pipe_tab, exec->nb_child - 1) != 0)
		return (ft_print_errors("pipes", 0), 1);
	code = exec_cmd(pl, parse, exec);
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

int	exec_main_loop(t_parser *parse, t_exec *exec)
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
			sig_setup_defaut();
			code = child_process(cur, exec, parse);
			exit(code);
		}
		else 
		{
			signal(SIGINT, SIG_IGN);
			code = wait_all_children(exec);
			sig_setup_mini();	
		}
		cur = cur->next;
	}
	sig_set_to_ignore();
	if (close_all_pipes(exec->pipe_tab, exec->nb_child - 1) != 0)
		return (1);
	return (code);
}

int	exec_main(t_parser *parse, t_env *env, t_minishell *mini)
{
	t_exec	*exec;
	int		code;

	if (!parse || !parse->top || !parse->top->argument[0])
		return (1);
	if (parse->size == 1)
	{
		exec = ft_calloc(1, sizeof(t_exec));
		if (!exec)
			return (ft_print_errors("malloc", 0), 1);
		exec->pipe_tab = NULL;
		exec->nb_child = 1;
		exec->env = env;
		exec->top = NULL;
		exec->mini = mini;
		code = exec_one(parse->top, parse, exec);
		free_exec(exec);
		return (code);
	}
	exec = exec_init(parse->size, parse->top, env, mini);
	if (!exec)
		return (1);
	code = exec_main_loop(parse, exec);
	free_exec(exec);
	return (code);
}
