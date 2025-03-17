/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/03/14 14:19:56 by qupollet         ###   ########.fr       */
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

int     main(int argc, char **argv, char **envp)
{
	if (argc != 1 || argv != NULL)
	{
		char		*string = NULL;
		t_lexer		*lexer = NULL;
		t_parser	*parse = NULL;

		while (string == NULL)
		{
			string = readline("Minishell$ ");
			if (string == NULL)
				return (free(string), EXIT_SUCCESS);
			else if (*string == '\0')
				free(string);
			else
			{
				lexer = mi_make_lexer(string);
				parse = mi_make_parse(parse, lexer);
				if (parse != NULL)
				{
					exec_main(parse, envp);
					ll_free_lexer(lexer);
					free_all_parser(parse);
					parse = NULL;
				}
			}
			free(string);
			string = NULL;
		}
	}
	return (EXIT_SUCCESS);
}
