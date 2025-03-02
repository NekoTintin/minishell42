/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 08:01:21 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/02 08:01:48 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser	*parse_make_parseur(t_lexer *lexer)
{
	lexer = parsing_valid_lexer(lexer);
	if (lexer == NULL || pars_quote(lexer))// !! leak memorie
		return (NULL);
	if (parse_cmd_list(lexer->header))
		return (NULL);
	return (NULL);
}	
