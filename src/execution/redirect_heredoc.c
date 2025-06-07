/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:50:20 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/07 05:19:45 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(STDIN_FILENO, "\n", 1);
	exit(130);
}

void	close_pipes(int hd_pipe[2], int p1, int p2)
{
	if (p1 == 1)
		if (close(hd_pipe[0]) == -1)
			perror("bash: close");
	if (p2 == 1)
		if (close(hd_pipe[1]) == -1)
			perror("bash: close");
}

int	ft_write_pipe(int fd, char *delim)
{
	char		*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
			return (0);
		if (ft_strncmp(input, delim, ft_strlen(delim)) == 0
			&& ft_strlen(input) == ft_strlen(delim))
			return (free(input), 0);
		if (write(fd, input, ft_strlen(input)) == -1)
			return (perror("bash: write"), free(input), -1);
		if (write(fd, "\n", 1) == -1)
			return (perror("bash: write"), free(input), -1);
		free(input);
	}
	return (1);
}

int	exec_heredoc_readline(t_redirect *red, int hd_pipe[2])
{
	pid_t		child;
	int			status;

	child = fork();
	if (child < 0)
		return (perror("bash: fork"), 1);
	if (child == 0)
	{
		signal(SIGINT, handle_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
		close_pipes(hd_pipe, 1, 0);
		if (ft_write_pipe(hd_pipe[1], red->file[0]) == -1)
			exit (1);
		close_pipes(hd_pipe, 0, 1);
		exit(0);
	}
	if (waitpid(child, &status, 0) == -1)
		return (ft_print_errors("waitpid", 0), 1);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (1);
	return (0);
}

int	exec_heredoc(t_redirect *red)
{
	int			hd_pipe[2];

	if (pipe(hd_pipe) == -1)
		return (ft_print_errors("pipe", 0), 1);
	if (exec_heredoc_readline(red, hd_pipe) != 0)
		return (close_pipes(hd_pipe, 1, 1), 1);
	if (dup2(hd_pipe[0], STDIN_FILENO) == -1)
	{
		close_pipes(hd_pipe, 1, 1);
		return (ft_print_errors("dup2", 0), 1);
	}
	close_pipes(hd_pipe, 1, 1);
	return (0);
}
