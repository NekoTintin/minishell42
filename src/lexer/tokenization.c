/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:25:00 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/24 02:43:23 by unbuntu          ###   ########.fr       */
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
        else if(index == -1)
            break ;//error fonct To Do
        else
            index++;
    }
}

int        le_assing_type(t_lexer *lexer, char *string, int index)
{
    if (string[index] == '<' || string[index] == '>' || string[index] == '|')
        //To DO
    else if (string[index] == 39 || string[index] == 34)
        end_index = le_handle_quotes(string, index);
    else if (string[index] == '$')
        end_index = le_variable_env(string, index);
    else if (string[index] != '\0')
        return (le_assing_word(lexer, string, index));    
    else
        //fonction error 
}

int         le_assing_word(t_lexer *lexer, char *string, int index)
{
    int     end_index;
    int     length;
    int     compteur;
    char     *word;
    t_tokenization  *curr;

    end_index = le_find_word(string, index);
    length = end_index - index;
    word = (char *)malloc(sizeof(char) * length + 1);
    if (word == NULL)
        return (-1);
    compteur = 0;
    while (compteur != length)
    {
        word[compteur] = string[index + compteur];
        compteur++;
    }
    word[length + 1] = '\0';
    lexer = ft_add_token(lexer);
    curr = le_last_node(lexer);
    curr->type = WORD;
    curr->value = ft_strdup(word);
    free(word);
    return(end_index + 1);
}