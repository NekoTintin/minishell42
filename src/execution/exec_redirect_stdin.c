/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_stdin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 16:15:31 by qupollet          #+#    #+#             */
/*   Updated: 2025/04/04 16:04:06 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

int	ft_redirect_infile(t_redirect *cur);
int	ft_redirect_heredoc(t_redirect *cur);

int	ft_redirect_input(t_cmd *cmd)
{
	t_redirect		*cur;
	int				code;

	code = 0;
	cur = cmd->redirect;
	while (cur)
	{
		if (cur->type == REDIRECT_IN)
		{
			code = ft_redirect_infile(cur);
			if (code != 0)
				return (code);
		}
		else if (cur->type == HEREDOC)
		{
			code = ft_redirect_heredoc(cur);
			if (code != 0)
				return (code);
		}
		cur = cur->next;
	}
	return (code);
}

int	ft_redirect_infile(t_redirect *cur)
{
	int				input_fd;

	input_fd = open(cur->file[0], O_RDONLY);
	if (input_fd < 0)
	{
		ft_print_errors(cur->file[0]);
		return (1);
	}
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		close(input_fd);
		perror("bash: dup2");
		return (1);
	}
	close(input_fd);
	return (0);
}

int	ft_write_in_pipe(int write_pipe, char *delim)
{
	char		*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
			return (0);
		/*if (exec_replace_env_var(&input) != 0)
			return (1);*/
		if (ft_strncmp(input, delim, ft_strlen(delim)) == 0)
			return (free(input), 0);
		if (write(write_pipe, input, ft_strlen(input)) == -1)
		{
			perror("bash: write");
			return (free(input), 1);
		}
		if (write(write_pipe, "\n", 1) == -1)
		{
			perror("bash: write");
			return (free(input), 1);
		}
		free(input);
	}
	return (1);
}

int	ft_read_lines(t_redirect *cur, int *heredoc_pipe)
{
	pid_t		child;

	child = fork();
	if (child < 0)
	{
		perror("bash: fork");
		return (1);
	}
	if (child == 0)
	{
		ft_close_pipe(heredoc_pipe, 1, 0);
		if (ft_write_in_pipe(heredoc_pipe[1], cur->file[0]) == 1)
		{
			ft_close_pipe(heredoc_pipe, 0, 1);
			exit (1);
		}
		ft_close_pipe(heredoc_pipe, 0, 1);
		exit (0);
	}
	waitpid(child, NULL, 0);
	return (0);
}

int	ft_redirect_heredoc(t_redirect *cur)
{
	int				heredoc_pipe[2];

	if (pipe(heredoc_pipe) == -1)
		return (perror("bash: pipe"), 1);
	if (ft_read_lines(cur, heredoc_pipe) == 1)
	{
		ft_close_pipe(heredoc_pipe, 1, 1);
		return (1);
	}
	if (dup2(heredoc_pipe[0], STDIN_FILENO) == -1)
	{
		ft_close_pipe(heredoc_pipe, 1, 1);
		perror("bash: dup2");
		return (1);
	}
	ft_close_pipe(heredoc_pipe, 1, 1);
	return (0);
}
