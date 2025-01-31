/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:45:21 by qupollet          #+#    #+#             */
/*   Updated: 2025/01/31 18:05:49 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "lexer.h"
#include "parsing.h"

int	ft_create_commands(t_lexer *lexer, t_parser *parser)
{
	int		iterator;
	int		nb_commands;

	iterator = 0;
	nb_commands = ft_command_counter(lexer);
	if (nb_commands < 0)
		return (-1);
	while (iterator < nb_commands)
		if (ft_init_command(parser) == -1)
			return (-1);
	return (0);
}

int	ft_parsing_loop(t_lexer *lexer, t_parser *parser)
{
	t_token			*token;
	t_cmd			*cmd;

	if (!lexer || !lexer->header || !parser || !parser->top)
		return (-1);
	token = lexer->header;
	cmd = parser->top;
	while (token)
	{
		if (token->type == PIPE)
		{
			cmd = cmd->next;
			if (!cmd)
				break ;
		}
		else
			ft_token_analyzer(token, cmd);
		token = token->next;
	}
	return (0);
}

t_parser	*parsing(t_lexer *lexer)
{
	t_parser	*parser;

	parser = ft_init_parser();
	if (!parser)
		return (NULL);
	if (ft_create_commands(lexer, parser) == -1)
		return (ft_free_parser(parser), NULL);
	if (ft_parser_loop(lexer, parsing) == -1)
	{
		ft_free_parser(parser);
		return (NULL);
	}
	return (parser);
}
