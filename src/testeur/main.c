/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/19 13:11:29 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void     print_chain(t_lexer *lexer);
static void     print_enum(int nb);
static int      test_mi_loop(char *string);

int     main(void)//int argc, char **argv)
{
    char    *string = NULL;

    while (string == NULL)
    {
        string = readline("");
        if (*string != '\0')
            test_mi_loop(string);
        string = NULL;
    }
    return (free(string), EXIT_SUCCESS);
}

static int     test_mi_loop(char *string)
{
    t_lexer     *lexer = mi_make_lexer(string);
    if (lexer == NULL || string == NULL)
        return (free(string), ll_free_lexer(lexer), 1);

    lexer = lx_clean_lexer(lexer);
    if (lexer == NULL || lexer->header == NULL)
        return (free(string), ll_free_lexer(lexer), 1);

    print_chain(lexer);
    ll_free_lexer(lexer);
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