/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/03/04 22:19:05 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "testeur.h"


void	print_parse(t_parser *parser);

void handle_sigint(int sig) {
    (void)sig;
    printf("\nMinishell$ ");
    fflush(stdout);
}

int     main(int argc, char **argv)//, char **envp)
{
    signal(SIGINT, handle_sigint);
    
    if (argc == 1)
	{
		char		*string = NULL;
		t_lexer		*lexer = NULL;

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
				print_lexer(lexer);
				test_mi_parse(lexer, string);
			}
			string = NULL;
			ll_free_lexer(lexer);
		}
	}
	else
	{
		char		*string = NULL;
		t_lexer		*lexer = NULL;
		int         fd = open (argv[1], O_RDONLY);;
		
		string = get_next_line(fd);
		lexer = mi_make_lexer(string);
		if (lexer == NULL)
			return (free(lexer),EXIT_FAILURE);
		test_mi_parse(lexer, string);
		while (string != NULL)
		{
			free(string);
			string = NULL;
			ll_free_lexer(lexer);
			string = get_next_line(fd);
			if (string == NULL)
				return (0);
			/*string = readline("Minishell$ ");
			if (string == NULL)
				return (free(string), EXIT_SUCCESS);
			else if (*string == '\0')
				free(string);    
			else*/
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

/*get_next_line (fd);
	printf ("%s", l);
	while (*l)
	{
		free (l);
		l = NULL;
		l = get_next_line(fd);
		if (l == NULL)
			return (0);
		printf ("%s", l);
	}
	free (l);
	l = NULL;
	close (fd);*/

