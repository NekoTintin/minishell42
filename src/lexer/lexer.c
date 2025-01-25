/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 03:57:57 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/25 18:02:13 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

t_lexer     *lx_value_chain(char *string, t_lexer *lexer)
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

t_lexer    *lx_tolkenization(t_lexer *lexer)
{
    // renvoyer le lexer avec les node tokeniser.
    return (lexer);
}







/*static void      le_error_index(t_lexer *lexer);
static int       le_assing_space(t_lexer *lexer, int index);


int        lx_assing_type(t_lexer *lexer, char *string)
{
    if (string[index] == '<' || string[index] == '>' || string[index] == '|')
        
    else if (string[index] == 39 || string[index] == 34)
       
    else if (string[index] == '$')
        
    else if (string[index] != '\0')
         
    return (-1); 
}


static int         le_assing_space(t_lexer *lexer, int index)
{
    t_token  *curr;
    char            *space;

    *space = 32;
    lexer = ft_add_token(lexer);
    curr = le_last_node(lexer);
    curr->value = ft_strdup(space);
    curr->type = WHITESPACE;
    return (index + 1);
}

static void      le_error_index(t_lexer *lexer)
{
    ft_free_lexer(lexer);
}*/