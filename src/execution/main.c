/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:11:19 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/27 19:19:45 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*string;
	t_lexer		*lexer;
	t_parser	*parse;
	t_env		*env;

	if (argc != 1 || argv != NULL)
	{
		string = NULL;
		lexer = NULL;
		parse = NULL;
		env = ft_create_tenv(envp);
		if (env == NULL)
			return (EXIT_FAILURE);
		while (string == NULL)
		{
			string = readline("Minishell$ ");
			add_history(string);
			if (string == NULL)
				return (free(string), EXIT_SUCCESS);
			else if (*string == '\0')
				free(string);
			else
			{
				lexer = mi_make_lexer(string);
				parse = mi_make_parse(parse, lexer);
				if (parse == NULL)
					return (EXIT_FAILURE);
				if (exec_main(parse, env) == -1)
					return (1);
				free_all_parser(parse);
				parse = NULL;
				free(string);
				string = NULL;
			}
		}
	}
	return (EXIT_SUCCESS);
}
