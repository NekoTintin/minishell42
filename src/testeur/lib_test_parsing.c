/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_test_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:54:05 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/05 10:45:11 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testeur.h"

void     test_mi_parse(t_lexer *lexer, char *string)
{
    t_parser    *parse = NULL;
    printf("test commande --> %s\n", string);
    if (parsing_valid_lexer(lexer))
        printf("ERROR_COMMAND_NOT_VALID \n");
    else 
    {
        lexer = parse_conc_quote(lexer);
        parse = parse_make_parser(parse);
        parse = parse_cmd_list(lexer->header, parse);
        printf("parser ast [OK]:\n");
        print_parse(parse);
        free_all_parser(parse);
    }
}

void	print_parse(t_parser *parse)
{
	t_cmd	*cmd;
	t_redirect	*redirect;

	cmd = parse->top;
	while (cmd != NULL)
	{
		for (int i = 0; cmd->argument[i] != NULL ; i++)
			printf("argument(%d)->%s\n", i, cmd->argument[i]);
		redirect = cmd->redirect;
		while (redirect != NULL)
		{
			printf("redirection : %s\n", print_enum(redirect->type));
			for (int i = 0; redirect->file[i] != NULL ; i++)
				printf("file(%d)->%s\n", i, redirect->file[i]);
			redirect = redirect->next;
		}
		cmd = cmd->next;
		printf("== END CMD ==\n");
	}
}