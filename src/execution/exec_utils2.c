/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:49:56 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/29 17:24:03 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_quit(t_parser *parse, t_exec *exec)
{
	close_all_pipes(exec->pipe_tab, parse->size - 1);
	free_int_tab(exec->pipe_tab, parse->size - 1);
	pipeline_free(exec->top);
	free(exec);
	free_all_parser(parse);
	parse = NULL;
}
