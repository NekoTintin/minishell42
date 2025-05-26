/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:36:40 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/05 19:43:42 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser	*mi_make_parse(t_parser *parse, t_lexer *lexer)
{
	if (lexer == NULL || lexer->header == NULL || parsing_valid_lexer(lexer))
	{
		printf("ERROR_COMMAND_NOT_VALID \n");
		return (NULL);
	}
	else
	{
		lexer = parse_conc_quote(lexer);
		if (lexer == NULL)
			return (ll_free_lexer(lexer), NULL);
		parse = parse_make_parser(parse);
		if (parse == NULL)
			return (ll_free_lexer(lexer), NULL);
		parse = parse_cmd_list(lexer->header, parse);
		if (parse == NULL)
			return (ll_free_lexer(lexer), NULL);
	}
	ll_free_lexer(lexer);
	return (parse);
}
