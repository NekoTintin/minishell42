/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 03:46:59 by qupollet          #+#    #+#             */
/*   Updated: 2025/03/18 14:42:58 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_redirects(t_cmd *cmd, int *p1, int *p2)
{
	int			return_code;

	(void)p1;
	(void)p2;
	if (ft_has_redirect(cmd, REDIRECT_IN) == 1)
	{
		return_code = ft_redirect_input(cmd);
		if (return_code != 0)
			return (return_code);
	}
	if (ft_has_redirect(cmd, REDIRECT_OUT) == 1)
	{
		return_code = ft_redirect_output(cmd);
		if (return_code != 0)
			return (return_code);
	}
	return (0);
}

int	ft_redirect_heredoc(t_cmd *cmd)
{
	int		heredoc_pipe[2];

	if (pipe(heredoc_pipe) == -1)
		return (perror("bash: pipe failed"), 1);

	if (dup2[heredoc_pipe[0], ])
	return (0);
}

// Duplicate the input in stdin, cmd->infile must be valid
int	ft_redirect_input(t_cmd *cmd)
{
	t_redirect		*cur;
	int				input_fd;

	input_fd = -1;
	cur = cmd->redirect;
	while (cur)
	{
		if (cur->type == REDIRECT_IN)
		{
			if (input_fd != -1)
				close(input_fd);
			input_fd = open(cur->file[0], O_RDONLY);
			if (input_fd < 0)
				return (ft_print_errors(cur->file[0]), 1);
		}
		cur = cur->next;
	}
	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			return (close(input_fd), perror("bash: dup2 failed"), 1);
		close(input_fd);
	}
	return (0);
}

// Duplicate the input in stdout, cmd->outfile and cmd->append must be valid
int	ft_redirect_output(t_cmd *cmd)
{
	t_redirect		*cur;
	int				output_fd;

	output_fd = -1;
	cur = cmd->redirect;
	while (cur)
	{
		if (cur->type == REDIRECT_OUT || cur->type == APPEND)
		{
			if (output_fd != -1)
				close(output_fd);
			output_fd = ft_open_file(cur->file[0], cur->type);
			if (output_fd < 0)
				return (ft_print_errors(cur->file[0]), -1);
		}
		cur = cur->next;
	}
	if (output_fd != -1)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
			return (close(output_fd), perror("bash: dup2 failed"), 1);
		close(output_fd);
	}
	return (0);
}
