/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 03:57:57 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/24 04:33:55 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer    *le_tolkenization(const char *string_readline, t_lexer *lexer)
{
    int     index;

    index = 0;
    while (string_readline[index] != '\0')
    {
        if (!le_isspace(string_readline[index]))
            index = le_assing_type(lexer, string_readline, index);
        else if(le_isspace(string_readline[index]))
            index++;
        else if(index == -1)
           break; //fonc error To Do
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
        return (index);
    else if (string[index] != '\0')
        return (le_assing_word(lexer, string, index));    
    return (-1); 
}