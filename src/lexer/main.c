/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/25 16:43:12 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void     print_chain(t_lexer *lexer);

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
    t_token *node = lexer->header;

    while (node != NULL)
    {
        printf("-> valeur node: %s \n", node->value);
        printf("-> type   node: %d \n", node->type);
        node = node->next;
    }
}
