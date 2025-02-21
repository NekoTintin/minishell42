/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/21 12:02:43 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void     print_chain(t_lexer *lexer);
static void     print_enum(int nb);
static t_lexer  *test_mi_lexer(char *string, t_lexer *lexer);
static void	    ft_print_parser(t_parser *parser);
int      test_process(void);

int     main(int argc, char **argv, char **envp)
{
    char        *string = NULL;
    t_lexer     *lexer = NULL;
    t_parser    *parser = NULL;
    
    if (argc != 1 && argv != NULL)
        return (EXIT_FAILURE);

    while (string == NULL)
    {
        string = readline("");
        if (*string != '\0')
        {
            lexer = test_mi_lexer(string, lexer);
            if (lexer == NULL)
                return (EXIT_FAILURE);
            parser = parsing(lexer, envp);
            if (parser != NULL)
            {
                ft_print_parser(parser);
                ft_printf("nomber of command (%d)\n", parser->size);
            }
        }
        string = NULL;
    }
    return (free(string), EXIT_SUCCESS);
}

static t_lexer     *test_mi_lexer(char *string, t_lexer *lexer)
{
    lexer = mi_make_lexer(string);
    if (lexer == NULL || string == NULL)
        return (free(string), ll_free_lexer(lexer), NULL);
    print_chain(lexer);
    return (lexer);
}

int      test_process(void)
{
    pid_t   pid = fork();
    if (pid < 0)
        perror("fail process");
    if (pid == 0) 
    { // Processus enfant
        char *args[] = {"ls", "-l", NULL};  // Tableau d'arguments (NULL à la fin)
        execvp(args[0], args);
        perror("execvp failed");  // Si execvp échoue
        exit(EXIT_FAILURE);
    } 
    else 
    { // Processus parent
        wait(NULL);  // Attend la fin de l'enfant
        printf("Parent : enfant terminé.\n");
    }
    return (0);
}

static void    print_chain(t_lexer *lexer)
{
    int     index = 0;
    t_token *node = lexer->header;

    while (node != NULL)
    {
        printf("======node:%d======\n", index);
        printf("-> valeur node: %s \n", node->value);
        printf("-> type   node:");
        print_enum(node->type);
        node = node->next;
    }
}

static void     print_enum(int nb)
{
    if (nb == 0)
        printf("WORD\n");
    if (nb == 1)
        printf("VAR_ENV\n");
    if (nb == 2)
        printf("S_QUOTES\n");
    if (nb == 3)
       printf("D_QUOTES\n");
    if (nb == 4)
        printf("PIPE\n");
    if (nb == 5)
        printf("REDIRECT_IN\n");
    if (nb == 6)
        printf("REDIRECT_OUT\n");
    if (nb == 7)
        printf("APPEND\n");
    if (nb == 8)
        printf("HEREDOC\n");
    if (nb == 9)
        printf("WHITESPACE\n");
    if (nb == 10)
       printf("UNKNOWN\n");
}

static void	ft_print_parser(t_parser *parser)
{
	t_cmd	*cmd;
	int		i;

	cmd = parser->top;
	while (cmd != NULL)
	{
		printf("\nNouvelle Commande\n");
		i = -1;
		printf("Args:\n");
		if (cmd->args)
			while (cmd->args[++i])
				printf(" - %s\n", cmd->args[i]);
		i = -1;
		printf("infile:\n");
		if (cmd->infile)
			while (cmd->infile[++i])
				printf(" - %s\n", cmd->infile[i]);
		else
			printf(" - (null)\n");
		i = -1;
		printf("outfile:\n");
		if (cmd->outfile)
			while (cmd->outfile[++i])
				printf(" - %s\n", cmd->outfile[i]);
		else
			printf(" - (null)\n");
		i = -1;
		printf("append:\n");
		if (cmd->append)
			while (cmd->append[++i] != -1)
				printf(" - outfile %d is append: %d\n", i, cmd->append[i]);
		else
			printf(" - (null)\n");
		printf("delimiter:\n");
		if (cmd->delimiter)
		{
			printf(" - %s\n", cmd->delimiter);
			printf(" - Delete tabs ? %d\n", cmd->delete_tabs);
		}
		else
			printf(" - (null)\n");
		cmd = cmd->next;
	}
}