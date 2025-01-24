/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 01:12:26 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/24 01:38:54 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int      le_isspace(const char *c)
{
    if (c == 32)
        return (1);
    return (0);
}

int   le_variable_env(char *string, int index_of_dollar)
{
    if (string[index_of_dollar] == '$')
    {
        while (string[index_of_dollar] != 32 || string[index_of_dollar] != '\0')
            index_of_dollar++;
        return (index_of_dollar);
    }
    return (index_of_dollar);
}

int     le_handle_quotes(char *string, int index_of_quote)
{
    int    memory_quote;
    int    size;

    if (string[index_of_quote] == 39 || string[index_of_quote] == 34)
    {
        memory_quote = string[index_of_quote];
        size = 1;
        while (string[index_of_quote + size] != memory_quote)
            size++;
        return (index_of_quote + size);
    }
    return (index_of_quote);
}

int     le_identify_synbols(char *string, int index_synbols)
{
    if (string[index_synbols + 1] == '>' || string[index_synbols + 1] == '<')
        return(index_synbols + 2);
    if (string[index_synbols + 1] != '>' || string[index_synbols + 1] != '<')
        return (index_synbols + 1);
}

int     le_find_word(char *string, int index_of_word)
{
    while (string[index_of_word] != 32 || string[index_of_word] != '\0')
        index_of_word++;
    return (index_of_word);
}