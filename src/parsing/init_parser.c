/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:38:11 by qupollet          #+#    #+#             */
/*   Updated: 2025/01/31 16:43:05 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "parsing.h"
#include "../../includes/minishell.h"

t_parser	*ft_init_parser(void)
{
	t_parser	*parser;

	parser = ft_calloc(1, sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->size = 0;
	parser->top = NULL;
	return (parser);
}

t_cmd	*ft_parser_last(t_parser *parser)
{
	t_cmd	*cur;

	cur = parser->top;
	while (cur && cur->next)
		cur = cur->next;
	return (cur);
}

int	ft_init_command(t_parser *parser)
{
	t_cmd	*command;
	t_cmd	*last;

	if (!parser)
		return (-1);
	command = ft_calloc(1, sizeof(t_cmd));
	if (!command)
		return (-1);
	command->append = -1;
	command->args = NULL;
	command->infile = NULL;
	command->outfile = NULL;
	command->next = NULL;
	command->is_builtin = -1;
	if (!parser->top)
		parser->top = command;
	else
	{
		last = ft_parser_last(parser);
		last->next = command;
	}
	parser->size++;
	return (0);
}

void	ft_free_parser(t_parser *parser)
{
	t_cmd		*cur;
	t_cmd		*next;
	int			i;

	if (!parser)
		return ;
	cur = parser->top;
	while (cur)
	{
		next = cur->next;
		free(cur->next);
		if (cur->infile)
			free(cur->infile);
		if (cur->outfile)
			free(cur->outfile);
		if (cur->args)
		{
			i = -1;
			while (cur->args[++i])
				free(cur->args[i]);
		}
		free(cur);
		cur = next;
	}
	free(parser);
}
