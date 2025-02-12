/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:45:21 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/12 02:27:44 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
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
	{
		if (ft_init_command(parser) == -1)
			return (-1);
		iterator++;
	}
	return (0);
}

int	ft_parsing_loop(t_token *token, t_cmd *cmd)
{
	while (token)
	{
		if (token->type == PIPE)
		{
			cmd = cmd->next;
			if (!cmd)
				return (-2);
		}
		else if (ft_get_symbol(token) > 0)
		{
			if (token->next == NULL && token->next->next == NULL)
				return (-3);
			if (ft_handle_symbol(token, cmd) == -1)
				return (-1);
			token = token->next->next;
		}
		else if (token->type == WORD)
			if (ft_handle_word(token, cmd) == -1)
				return (-1);
		token = token->next;
	}
	return (0);
}

int	ft_parser_start(t_lexer *lexer, t_parser *parser)
{
	t_token			*token;
	t_cmd			*cmd;
	int				output;

	if (!lexer || !lexer->header || !parser || !parser->top)
		return (-1);
	token = lexer->header;
	cmd = parser->top;
	output = ft_parsing_loop(token, cmd);
	if (output < 0)
		return (output);
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
	if (ft_parser_start(lexer, parser) == -1)
		return (ft_free_parser(parser), NULL);
	return (parser);
}
