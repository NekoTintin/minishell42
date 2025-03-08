/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 03:46:59 by qupollet          #+#    #+#             */
/*   Updated: 2025/03/08 19:06:49 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_errors(char *filename)
{
	ft_putstr_fd("bash: ", 2);
	perror(filename);
}

int	ft_redirect_heredoc(t_cmd *cmd)
{
	return (-1);
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
			return (perror("bash: dup2 failed"), 1);
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
			output_fd = ft_check_open_file(cur->file[0], cur->type);
			if (output_fd < 0)
				return (ft_print_errors(cur->file[0]), -1);
		}
		cur = cur->next;
	}
	if (output_fd != -1)
	{
		if (dup2(output_fd, STDOUT_FILENO) == -1)
			return (perror("bash: dup2 failed"), -1);
		close(output_fd);
	}
	return (0);
}
