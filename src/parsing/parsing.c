/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 00:45:21 by qupollet          #+#    #+#             */
/*   Updated: 2025/01/29 20:52:42 by qupollet         ###   ########.fr       */
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

t_parser	*parsing(t_lexer *lexer)
{
	t_parser	*parser;

	parser = ft_init_parser();
	if (!parser)
		return (NULL);
	(void)lexer;
	return (parser);
}
