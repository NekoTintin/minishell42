/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:50:51 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/28 19:05:51 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
int	child_process(t_pipeline *pl, t_exec *exec)
{
	int			code;

	return (1);
}

int	exec_run(t_exec *exec)
{
	t_pipeline	*cur;
	int			code;

	code = 0;
	cur = exec->top;
	while (cur)
	{
		cur->pid = fork();
		if (cur->pid < 0)
			return (ft_print_errors("fork"), 1);
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

int	exec_main(t_parser *parser, t_env *env)
{
	//t_exec	*exec;

	if (!parser || !parser->top || !parser->top->argument[0])
		return (1);
	if (parser->size == 1)
		return (exec_one(parser->top, env) != 0);
	//exec = ft_calloc(1, sizeof(t_exec));
	//if (!exec)
	//	return (1);
	//exec->nb_child = parser->size;
	//exec->env = env;
	//exec->top = ft_create_pipeline(exec->nb_child, parser->top);
	//if (!exec->top)
	//	return (1);
	return (0);
}
