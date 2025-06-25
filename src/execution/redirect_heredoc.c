/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 18:50:20 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/24 23:48:56 by qupollet         ###   ########.fr       */
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
		if (!g_sig && !input)
			return (0);
		if (g_sig)
		{
			g_sig = 0;
			return (free(input), 130);
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

int	exec_heredoc_loop(t_cmd *cmd, t_redirect *red)
{
	int					fd;
	int					code;

	fd = heredoc_file(cmd);
	if (fd == -1)
		return (1);
	code = ft_write_fd(fd, red->file[0]);
	close(fd);
	if (code != 0)
		return (code);
	return (0);
}

int	exec_heredoc(t_cmd *cmd)
{
	t_redirect		*red;
	int				code;

	code = 0;
	red = cmd->redirect;
	while (red)
	{
		if (red->type == HEREDOC)
		{
			code = exec_heredoc_loop(cmd, red);
			if (code != 0)
				return (code);
		}
		red = red->next;
	}
	return (0);
}

int	pipeline_read_all_heredoc(t_cmd *cmd)
{
	t_cmd			*cur;
	int				code;

	if (!cmd)
		return (1);
	cur = cmd;
	while (cur)
	{
		code = exec_heredoc(cur);
		if (code != 0)
		{
			if (code != 130)
				ft_print_errors("heredoc", code);
			return (code);
		}
		cur = cur->next;
	}
	return (0);
}
