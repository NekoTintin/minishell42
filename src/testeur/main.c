/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/03/05 19:46:11 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "testeur.h"


void	print_parse(t_parser *parser);
char	**cp_array_env(char **envp, int length);
int	ft_arrlen(char **array);
void	print_env_array(char **var_env);

void handle_sigint(int sig) {
    (void)sig;
    printf("\nMinishell$ ");
    fflush(stdout);
}

int     main(int argc, char **argv, char **envp)
{
    signal(SIGINT, handle_sigint);
    
    if (argc != 1 || argv != NULL)
	{
		char		*string = NULL;
		char		**var_env = NULL;
		t_lexer		*lexer = NULL;
		t_parser	*parse = NULL;
		var_env = cp_array_env(envp, 0);
		print_env_array(var_env);
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
				print_lexer(lexer);
				printf("\n");
				parse = mi_make_parse(parse, lexer);
				if (parse == NULL)
					return (EXIT_FAILURE);
				print_parse(parse);
				//exec_main(parse, var_env);
				free_all_parser(parse);
				parse = NULL;
				free(string);
				string = NULL;
				
			}
		}
	free_array(var_env);	
	}
	return (EXIT_SUCCESS);
}
	/*
	else
	{
		char		*string = NULL;
		t_lexer		*lexer = NULL;
		int         fd = open (argv[1], O_RDONLY);;
		
		string = get_next_line(fd);
		lexer = mi_make_lexer(string);
		if (lexer == NULL)
			return (free(lexer),EXIT_FAILURE« ft_arrlen );
		test_mi_parse(lexer, string);
		while (string != NULL)
		{
			free(string);
			string = NULL;
			ll_free_lexer(lexer);
			string = get_next_line(fd);
			if (string == NULL)
				return (0);
				// -- test_mi_lexer(string); --	
			lexer = mi_make_lexer(string);
			if (lexer == NULL)
				return (free(lexer),EXIT_FAILURE);
			test_mi_parse(lexer, string);
			printf("\n");
			//free(string);
			//string = NULL;
			//ll_free_lexer(lexer);
		}
		close(fd);
	}
    return (EXIT_SUCCESS);
}
*/

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
