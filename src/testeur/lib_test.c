/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:08:38 by bchallat          #+#    #+#             */
/*   Updated: 2025/02/25 14:56:44 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testeur.h"

t_lexer     *test_mi_lexer(char *string, t_lexer *lexer)
{
    lexer = mi_make_lexer(NULL);
    if (lexer == NULL)
        printf("test lexer NULL \n");

    lexer = mi_make_lexer("\0");
    if (lexer != NULL)
        printf("test lexer void \n");
    
    lexer = mi_make_lexer(string);
    if (lexer == NULL || string == NULL)
        return (NULL);
    
    print_lexer(lexer);
    return (lexer);
}

void    print_lexer(t_lexer *lexer)
{
    t_token *node = lexer->header;
    printf("number of token -> (%d)\n", lexer->size);
    while (node != NULL)
    {
        printf("[valeur node(%d): %s, %s ]  \n",node->index, node->value, print_enum(node->type));
        node = node->next;
    }
    printf("\n-- END LEXER --\n");
}

char     *print_enum(int nb)
{
    if (nb == 0)
        return ("WORD");
    if (nb == 1)
        return ("VAR_ENV");
    if (nb == 2)
        return ("S_QUOTES");
    if (nb == 3)
       return ("D_QUOTES");
    if (nb == 4)
        return ("PIPE");
    if (nb == 5)
        return ("REDIRECT_IN");
    if (nb == 6)
        return ("REDIRECT_OUT");
    if (nb == 7)
        return ("APPEND");
    if (nb == 8)
        return ("HEREDOC");
    if (nb == 9)
        return ("WHITESPACE");
    if (nb == 10)
       return ("UNKNOWN");
    return ("ERROR_TYPE");
}

