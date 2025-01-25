/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 03:57:57 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/25 20:22:34 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_lexer     *lx_value_chain(char *string, t_lexer *lexer);
static t_lexer    *lx_tolkenization(t_lexer *lexer);
static int        lx_assing_type(t_token *node);

t_lexer     *mi_make_lexer(char *readline_string)
{
    t_lexer     *lexer;
    
    lexer = ll_init_lexer(lexer);
    if (lexer == NULL || readline_string == NULL)
        return(ll_free_lexer(lexer), NULL);
    lexer = lx_value_chain(readline_string, lexer);
    if(lexer == NULL)
        return (NULL);
    lexer = lx_tolkenization(lexer);
    return (lexer);
}

static t_lexer     *lx_value_chain(char *string, t_lexer *lexer)
{
    int         index;
    t_token     *node;

    index = 0;
    while (string[index] != '\0')
    {
        if(string[index] == 32)
            index = lx_space_token(index, lexer);
        else
            index = lx_value_node(index, string, lexer);
        if(index == -1)
           return (NULL);
    }
    return (lexer);
}

static t_lexer    *lx_tolkenization(t_lexer *lexer)
{
    t_token     *curr;
    int         error_code;

    curr = lexer->header;
    while (curr != NULL)
    {
        if(curr->type != WHITESPACE)
            error_code = lx_assing_type(curr);
        curr = curr->next;
    }    
    return (lexer);
}

static int        lx_assing_type(t_token *node)
{
    if (node->value[0] == '<' || node->value[0] == '>' || node->value[0] == '|')
        return (-1);
    else if (node->value[0] == '$')
        return (-1);
    else if (node->value[0] == 34 || node->value[0] == 39)
        return (-1);
    else if (ft_isascii(node->value[0]))
        return (-1);
    return (-1); 
}