/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/27 14:45:24 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static void     print_chain(t_lexer *lexer);
static char     print_enum(int nb);

int     main(int argc, char **argv)
{
    t_lexer     *lexer = mi_make_lexer(argv[1]);
    if(lexer == NULL)
        return (EXIT_FAILURE);
    print_chain(lexer);
    ll_free_lexer(lexer);
    return (EXIT_SUCCESS);
}

static void    print_chain(t_lexer *lexer)
{
    int     index = 1;
    t_token *node = lexer->header;

    while (node != NULL)
    {
        printf("======node:%d======\n", index);
        printf("-> valeur node: %s \n", node->value);
        printf("-> type   node:");
        print_enum(node->type);
        node = node->next;
        index++;
    }
}

static char     print_enum(int nb)
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