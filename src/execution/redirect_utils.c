/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:05:03 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/25 14:02:26 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	search_red(t_cmd *cmd, t_token_type type)
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

void	free_heredoc(t_cmd *top)
{
	t_cmd		*cur;

	if (!top)
		return ;
	cur = top;
	while (cur)
	{
		if (cur->heredoc)
		{
			if (unlink(cur->heredoc) == -1)
				perror("unlink");
			free(cur->heredoc);
			cur->heredoc = NULL;
		}
		cur = cur->next;
	}
}

int	ft_check_redir_file(char *file, t_token_type type)
{
	int		fd;

	if (type == REDIRECT_IN)
	{
		fd = file_read(file);
		if (fd == -1)
			return (1);
		close(fd);
	}
	else if (type == REDIRECT_OUT || type == APPEND)
	{
		fd = file_write(file, type);
		if (fd == -1)
			return (1);
		close(fd);
	}
	return (0);
}

int	redir_verifs(t_cmd *cmd)
{
	t_cmd		*cur;
	t_redirect	*red;
	int			code;
	int			ret;

	cur = cmd;
	code = 0;
	ret = 0;
	while (cur)
	{
		red = cur->redirect;
		while (red)
		{
			if ((red->type == REDIRECT_IN || red->type == REDIRECT_OUT
					|| red->type == APPEND))
			{
				code = ft_check_redir_file(red->file[0], red->type);
				if (code != 0)
					ret = code;
			}
			red = red->next;
		}
		cur = cur->next;
	}
	return (ret);
}

// A tester avec le heredoc, je ne suis pas sûr si
// il faut fermer les pipes en cas d'échec
int	redir_prepare(t_parser *parse, t_exec *exec)
{
	int			code;

	code = 0;
	code = pipeline_read_all_heredoc(parse->top);
	if (code != 0)
	{
		if (exec->pipe_tab)
			if (close_all_pipes(exec->pipe_tab, exec->nb_child - 1) != 0)
				return (1);
		return (code);
	}
	code = redir_verifs(parse->top);
	if (code != 0)
	{
		if (exec->pipe_tab)
			if (close_all_pipes(exec->pipe_tab, exec->nb_child - 1) != 0)
				return (1);
		return (code);
	}
	return (code);
}
