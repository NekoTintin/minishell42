/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_rules_grammar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:23:23 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/02/28 10:23:26 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	CommandList -> Command | Command '|' CommandList
	Command -> SimpleCommand RedirectionList
	SimpleCommand -> WORD SimpleCommand | WORD
	RedirectionList -> Redirection RedirectionList | ε
	Redirection -> '<' WORD | '>' WORD | '>>' WORD | ...
*/

int	parse_command_list();
int	parse_command();
int	parse_simple_command();
int	parse_redirection_list();
int	parse_redirection();

int	parse_commande_list(t_lexer *lexer)
{
	if (lexer == NULL || lexer->header == NULL)
		return (-1);
	while (/*condition*/)
	{
		/* instruction*/
	}
	return (0);
}

int	parse_commande(t_lexer *lexer)
{
	if (lexer == NULL || lexer->header == NULL)
		return (-1);
	if ()
}
