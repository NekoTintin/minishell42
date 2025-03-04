/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/03/04 20:17:24 by benoitchallat    ###   ########.fr       */
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
//    signal(SIGINT, handle_sigint);
    
    if (argc != 1 && argv != NULL)
        return (EXIT_FAILURE);

	char		*string = NULL;
	t_lexer		*lexer = NULL;
	//t_parser	*parse = NULL;

    while (string == NULL)
    {
        string = readline("Minishell$ ");
        if (string == NULL)
            return (free(string), EXIT_SUCCESS);
        else if (*string == '\0')
            free(string);
        else
        {
		lexer = test_mi_lexer(string, lexer);
		if (lexer == NULL)
			return (free(lexer),EXIT_FAILURE);
		
		lexer = parse_conc_quote(lexer);
		print_lexer(lexer);
		/*parse = parse_make_parser(parse);
		parse = parse_cmd_list(lexer->header, parse);
		if (parse == NULL || parse->top == NULL)
			printf(" -- NULL --\n");
		printf(" -- END AST -- \n");	
		print_parse(parse);*/
        		
        }
        string = NULL;
	ll_free_lexer(lexer);
	//free_all_parser(parse);
	//parse = NULL;
    }
    return (free(string), EXIT_SUCCESS);
}

void	print_parse(t_parser *parse)
{
	t_cmd	*cmd;

	cmd = parse->top;
	while (cmd != NULL)
	{
		for (int i = 0; cmd->argument[i] != NULL ; i++)
			printf("argument(%d)->%s\n", i, cmd->argument[i]);
		if (cmd->redirect != NULL)
		{
			printf("redirection : %s\n", print_enum(cmd->redirect->type));
			for (int i = 0; cmd->redirect->file[i] != NULL ; i++)
				printf("file(%d)->%s\n", i, cmd->redirect->file[i]);
		}
		cmd = cmd->next;
		printf("== END CMD ==\n");
	}
}
