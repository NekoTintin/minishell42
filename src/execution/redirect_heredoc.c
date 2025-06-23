/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:50:20 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/23 18:31:54 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_write_fd(int fd, char *delim)
{
	char		*input;
	char		*new;

	while (1)
	{
		input = readline("> ");
		if (!input)
			return (0);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		if (ft_strncmp(input, delim, ft_strlen(delim)) == 0
			&& ft_strlen(input) == ft_strlen(delim))
			return (free(input), 0);
		new = ft_strdup(input);
		free(input);
		if (!new)
			return (1);
		if (write(fd, new, ft_strlen(new)) == -1 || write(fd, "\n", 1) == -1)
			return (perror("bash: write"), free(new), -1);
		free(new);
	}
	return (1);
}

int	exec_heredoc_loop(t_redirect *red, int counter)
{
	int			fd;
	int			code;
	static int	heredoc_count;

	fd = heredoc_file(red);
	if (fd == -1)
		return (1);
	code = ft_write_fd(fd, red->file[0]);
	close(fd);
	heredoc_count++;
	printf("counter: %d | heredoc_count: %d\n", counter, heredoc_count);
	if (heredoc_count < counter)
	{
		if (unlink(red->heredoc) == -1)
			return (ft_print_errors(red->heredoc, 126), 1);
	}
	if (code != 0)
		return (code);
	return (0);
}

int	heredoc_number(t_redirect *red)
{
	int			counter;
	t_redirect	*cur;

	cur = red;
	counter = 0;
	while (cur)
	{
		if (cur->type == HEREDOC)
			counter++;
		cur = cur->next;
	}
	return (counter);
}

int	exec_heredoc(t_cmd *cmd)
{
	t_redirect		*red;
	int				code;
	int				counter;

	code = 0;
	red = cmd->redirect;
	counter = heredoc_number(red);
	while (red)
	{
		if (red->type == HEREDOC)
		{
			code = exec_heredoc_loop(red, counter);
			if (code != 0)
				return (code);
		}
		red = red->next;
	}
	return (0);
}
