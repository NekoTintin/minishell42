/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/03/12 14:46:38 by qupollet         ###   ########.fr       */
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
	//signal(SIGINT, handle_sigint);

	parse = NULL;
	string = NULL;
	lexer = NULL;
	if (argc != 1 || argv != NULL)
	{
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
				exec_main(parse, envp);
			}
			free(string);
			string = NULL;
			ll_free_lexer(lexer);
		}
	}
	return (EXIT_SUCCESS);
}
