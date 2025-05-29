/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:53:34 by bchallat          #+#    #+#             */
/*   Updated: 2025/05/28 21:12:18 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\nMinishell$");
	fflush(stdout);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_lexer		*lexer;
	t_parser	*parse;
	t_env		*env;

	line = NULL;
	parse = NULL;
	lexer = NULL;
	signal(SIGINT, handle_sigint);
	if (argc == 1 && argv[1] == NULL)
	{
		while (line == NULL)
		{
			line = readline("Minishell$ ");
			add_history(line);
			if (line == NULL)
				return (free(line), rl_clear_history(), EXIT_SUCCESS);
			else if (line[0] == '\0')
			{
				free(line);
				line = NULL;
			}
			else
			{
				lexer = mi_make_lexer(line);
				parse = mi_make_parse(parse, lexer);
				if (parse == NULL)
					return (EXIT_FAILURE);
				env = ft_create_tenv(envp);
				if (!env)
				{
					free(line);
					line = NULL;
					ft_free_env(env);
					return (EXIT_FAILURE);
				}
				if (exec_main(parse, env) == -1)
				{
					ft_free_env(env);
					free_all_parser(parse);
					free(line);
					line = NULL;
					return (EXIT_FAILURE);
				}
				free_all_parser(parse);
				parse = NULL;
				free(line);
				line = NULL;
			}
		}
		rl_clear_history();
	}
	return (EXIT_SUCCESS);
}
