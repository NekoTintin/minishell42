/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:53:34 by bchallat          #+#    #+#             */
/*   Updated: 2025/05/26 11:53:38 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_parse(t_parser *parser);
char	**cp_array_env(char **envp, int length);
int	ft_arrlen(char **array);
void	print_env_array(char **var_env);

void handle_sigint(int sig)
{
    (void)sig;
    printf("\nMinishell$");
    fflush(stdout);
}

int     main(int argc, char **argv, char **envp)
{
    signal(SIGINT, handle_sigint);
    
    if (argc == 1 && argv[1] == NULL)
	{
		char		*line = NULL;
		char		**var_env = NULL;
		t_lexer		*lexer = NULL;
		t_parser	*parse = NULL;
		
		var_env = cp_array_env(envp, 0);
		while (line == NULL)
		{
			line = readline("Minishell$");
			add_history(line);
			if (line == NULL)
				return (free(line),free_array(var_env),rl_clear_history(), EXIT_SUCCESS);
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

char	**cp_array_env(char **envp, int length)
{
	char	**var_env;
	int	index;

	var_env = (char **)ft_calloc(ft_arrlen(envp) + 1 + length, sizeof(char *));
	if (var_env == NULL)
     		return (NULL);
	index = 0;
	while (envp != NULL && envp[index] != NULL)
	{
		var_env[index] = ft_strdup(envp[index]);
		if (var_env[index] == NULL)
			return (NULL);
		index++;
	}
	return (var_env);
}

int	ft_arrlen(char **array)
{
	int	index;

	index = 0;
	while (array[index] != NULL)
		index++;
	return (index);
}

void	print_env_array(char **var_env)
{
	int	index;

	index = 0;
	while (var_env[index] !=  NULL)
	{
		printf("export %s\n", var_env[index]);
		index++;
	}
}
