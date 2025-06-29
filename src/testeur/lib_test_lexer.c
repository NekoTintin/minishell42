/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_test_lexer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:08:38 by bchallat          #+#    #+#             */
/*   Updated: 2025/05/28 21:11:30 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testeur.h"

void     test_mi_lexer(char *string)
{
    t_lexer     *lexer;
    
    lexer = NULL;
    lexer = mi_make_lexer(NULL);
    if (lexer == NULL)
        printf("test lexer NULL \n");

    lexer = mi_make_lexer("\0");
    if (lexer != NULL)
        printf("test lexer void \n");
    
    lexer = mi_make_lexer(string);
    if (lexer != NULL || string != NULL)
       // print_lexer(lexer);
    ll_free_lexer(lexer);
}

void    print_lexer(t_lexer *lexer)
{
    t_token *curr;

    curr = lexer->header;
    while(curr != NULL)
    {
        printf("[%s : %s]\n", curr->value, print_enum(curr->type));
        curr = curr->next;
    }
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

