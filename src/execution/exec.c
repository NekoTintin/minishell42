/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:50:51 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/27 17:03:35 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_loop(t_exec *exec)
{
	
}

int	exec_main(t_parser *parser, t_env *env)
{
	t_exec	*exec;

	if (!parser || !parser->top || !parser->top->argument[0])
		return (1);
	exec = ft_calloc(1, sizeof(t_exec));
	if (!exec)
		return (1);
	exec->nb_child = parser->size;
	exec->env = env;
	exec->top = ft_create_pipeline(exec->nb_child, parser->top);
	if (!exec->top)
		return (1);
	return (0);
}
