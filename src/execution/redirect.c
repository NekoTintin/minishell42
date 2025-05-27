/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:17:11 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/27 18:31:24 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	search_redirect(t_cmd *cmd, t_token_type type)
{
	t_redirect	*cur;

	cur = cmd->redirect;
	while (cur)
	{
		if (cur->type == type)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int	exec_redirect_output(t_pipeline *pl)
{
	t_redirect	*cur;
	int			fd;

	fd = -1;
	cur = pl->cmd->redirect;
	while (cur)
	{
		if (cur->type == REDIRECT_OUT || cur->type == APPEND)
		{
			if (fd != -1)
				close(fd);
			fd = file_write(cur->file[0], cur->type);
			if (fd < 0)
				return (1);
		}
		cur = cur->next;
	}
	if (fd != -1)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), ft_print_errors("dup2"), 1);
		close(fd);
	}
	return (0);
}

int	ft_redirects(t_pipeline *pl)
{
	int		return_code;

	// Gérer les redirections d'entrée ici
	if (search_redirect(pl->cmd, REDIRECT_OUT)
		|| search_redirect(pl->cmd, APPEND))
	{
		return_code = exec_redirects_output(pl);
		if (return_code != 0)
			return (return_code);
	}
	else if (pl->pipe_in[0])
	{
		if (dup2(pl->pipe_in[0], STDIN_FILENO) == -1)
			return (ft_print_errors("dup2"), 1);
	}
	return (0);
}
