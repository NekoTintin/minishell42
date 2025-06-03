/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:50:20 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/03 22:34:20 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	write(STDIN_FILENO, "\n", 1);
	exit(130);
}

int	exec_heredoc_readline(void)
{
	pid_t		child;

	child = fork();
	if (child < 0)
		return (perror("bash: fork"), 1);
	if (child == 0)
	{
		(void)child;
	}
	waitpid(child, NULL, 0);
	return (0);
}

int	exec_heredoc(t_cmd *cmd)
{
	(void)cmd;
}
