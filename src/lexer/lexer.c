/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 03:57:57 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/24 06:02:50 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void      le_error_index(t_lexer *lexer);
static int         le_assing_space(t_lexer *lexer, int index);

t_lexer    *le_tolkenization(const char *string_readline, t_lexer *lexer)
{
    int     index;

    index = 0;
    while (string_readline[index] != '\0')
    {
        if (!le_isspace(string_readline[index]))
            index = le_assing_type(lexer, string_readline, index);
        else if(le_isspace(string_readline[index]))
            index = le_assing_space(lexer, index);
        else if(index == -1)
           return(le_error_index(lexer), NULL);
        else
            break;
    }
}

int        le_assing_type(t_lexer *lexer, char *string, int index)
{
    if (string[index] == '<' || string[index] == '>' || string[index] == '|')
        return (le_assing_synbols(lexer, string, index));
    else if (string[index] == 39 || string[index] == 34)
        return (le_assing_quotes(lexer, string, index));
    else if (string[index] == '$')
        return (le_assing_env(lexer, string, index));
    else if (string[index] != '\0')
        return (le_assing_word(lexer, string, index));    
    return (-1); 
}

static int         le_assing_space(t_lexer *lexer, int index)
{
    t_tokenization  *curr;
    lexer = ft_add_token(lexer);
    curr = le_last_node(lexer);
    curr->value = 32;
    curr->type = WHITESPACE;
    return (index + 1);
}

static void      le_error_index(t_lexer *lexer)
{
    ft_free_lexer(lexer);
}