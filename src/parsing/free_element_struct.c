/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_element_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:47:09 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/05/27 13:04:47 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		free_all_parser(t_parser *parser);
void		free_all_command(t_cmd *cmd);
void		free_all_redirect(t_redirect *redirect);
void		free_array(char **array);

void	free_all_parser(t_parser *parser)
{
	if (parser != NULL)
	{
		if (parser->top != NULL)
			free_all_command(parser->top);
		free(parser);
	}
}

void	free_all_command(t_cmd *cmd)
{
	t_cmd	*curr_f;

	if (cmd != NULL)
	{
		while (cmd != NULL)
		{
			curr_f = cmd;
			cmd = cmd->next;
			if (curr_f->argument != NULL)
				free_array(curr_f->argument);
			if (curr_f->redirect != NULL)
				free_all_redirect(curr_f->redirect);
			free(curr_f->heredoc);
			free(curr_f);
		}
	}
}

void	free_all_redirect(t_redirect *redirect)
{
	t_redirect	*curr_f;

	if (redirect != NULL)
	{
		while (redirect != NULL)
		{
			curr_f = redirect;
			redirect = redirect->next;
			if (curr_f->file != NULL)
				free_array(curr_f->file);
			free(curr_f);
		}
	}
}

void	free_array(char **array)
{
	int	index;

	if (array != NULL)
	{
		index = 0;
		while (array[index] != NULL)
		{
			if (array[index] != NULL)
				free(array[index]);
			index++;
		}
		free(array);
	}
}
