/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:17:11 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/07 04:23:24 by qupollet         ###   ########.fr       */
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

int	exec_redirect_output(t_cmd *cmd)
{
	t_redirect	*cur;
	int			fd;

	fd = -1;
	cur = cmd->redirect;
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
			return (close(fd), ft_print_errors("dup2", 0), 1);
		close(fd);
	}
	return (0);
}

int	exec_redir_infile(t_redirect *red)
{
	int			fd;

	fd = open(red->file[0], O_RDONLY);
	if (fd < 0)
	{
		ft_print_errors(red->file[0], 0);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		ft_print_errors("dup2", 0);
		return (1);
	}
	close(fd);
	return (0);
}

int	exec_redirect_input(t_cmd *cmd)
{
	t_redirect	*cur;
	int			code;

	code = 0;
	cur = cmd->redirect;
	while (cur)
	{
		if (cur->type == REDIRECT_IN)
		{
			code = exec_redir_infile(cur);
			if (code != 0)
				return (code);
		}
		else if (cur->type == HEREDOC)
		{
			code = exec_heredoc(cur);
			if (code != 0)
				return (code);
		}
		cur = cur->next;
	}
	return (code);
}

int	ft_redirects(t_cmd *cmd, int p1, int p2)
{
	int		return_code;

	if (search_redirect(cmd, REDIRECT_IN) || search_redirect(cmd, HEREDOC))
	{
		return_code = exec_redirect_input(cmd);
		if (return_code != 0)
			return (return_code);
	}
	else if (p1 != STDIN_FILENO)
	{
		if (dup2(p1, STDIN_FILENO) == -1)
			return (ft_print_errors("dup2", 0), 1);
	}
	if (search_redirect(cmd, REDIRECT_OUT) || search_redirect(cmd, APPEND))
	{
		return_code = exec_redirect_output(cmd);
		if (return_code != 0)
			return (return_code);
	}
	else if (p2 != STDOUT_FILENO)
	{
		if (dup2(p2, STDOUT_FILENO) == -1)
			return (ft_print_errors("dup2", 0), 1);
	}
	return (0);
}
