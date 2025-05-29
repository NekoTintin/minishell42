/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:50:51 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/29 17:39:42 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
int	child_process(t_pipeline *pl, t_exec *exec)
{
	int		code;
	char	*ntab;

	close()
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
			if (code != 0)
				exit(code);
		}
		cur = cur->next;
	}
	return (code);
}*/

int	exec_main(t_parser *parse, t_env *env)
{
	t_exec	*exec;

	if (!parse || !parse->top || !parse->top->argument[0])
		return (1);
	// if (parse->size == 1)
		// return (exec_one(parse->top, env) != 0);
	exec = exec_init(parse->size, parse->top, env);
	if (!exec)
		return (1);
	printf("nb_child: %d\n", exec->nb_child);
	print_pipeline(exec->top);
	return (0);
}
