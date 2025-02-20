/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:45:21 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/20 19:59:02 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	ft_parsing_loop(t_token *token, t_cmd *cmd, char **envp)
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
			if (ft_handle_symbol(token, cmd) == -1)
				return (-1);
			if (token->next && token->next->value[0] == '-')
				token = token->next;
			if (token->next)
				token = token->next;
		}
		else if (token->type == WORD || token->type == D_QUOTES
			|| token->type == S_QUOTES || token->type == VAR_ENV)
			if (ft_handle_word(token, cmd, envp) == -1)
				return (-1);
		token = token->next;
	}
	return (0);
}

int	ft_parser_start(t_lexer *lexer, t_parser *parser, char **envp)
{
	t_token			*token;
	t_cmd			*cmd;
	int				output;

	if (!lexer || !lexer->header || !parser || !parser->top)
		return (-1);
	token = lexer->header;
	cmd = parser->top;
	output = ft_parsing_loop(token, cmd, envp);
	if (output < 0)
		return (output);
	return (0);
}

t_parser	*parsing(t_lexer *lexer, char **envp)
{
	t_parser	*parser;

	parser = ft_init_parser();
	if (!parser)
		return (NULL);
	lx_clean_lexer(lexer);
	if (ft_create_commands(lexer, parser) == -1)
		return (ft_free_parser(parser), NULL);
	if (ft_parser_start(lexer, parser, envp) == -1)
		return (ft_free_parser(parser), NULL);
	return (parser);
}
