/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/04/15 19:47:58 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "testeur.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\nMinishell$ ");
	fflush(stdout);
}

int	main(int argc, char **argv, char **envp)
{
	char		*string;
	t_lexer		*lexer;
	t_parser	*parse;
	int			exit_status;

	(void)argv;
	lexer = NULL;
	parse = NULL;
	if (argc != 1)
		return (EXIT_FAILURE);
	while (1)
	{
		string = readline("Minishell$ ");
		if (!string)
			return (EXIT_SUCCESS);
		if (*string == '\0')
		{
			free(string);
			continue ;
		}
		//add_history(string);
		lexer = mi_make_lexer(string);
		free(string);
		if (!lexer)
			return (EXIT_FAILURE);
		parse = mi_make_parse(parse, lexer);
		if (!parse)
			return (ll_free_lexer(lexer), 1);
		exit_status = exec_main(parse, envp);
		(void)exit_status;
		ll_free_lexer(lexer);
		free_all_parser(parse);
		lexer = NULL;
		parse = NULL;
		
	}
	return (EXIT_SUCCESS);
}
