/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:25:00 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/24 04:30:20 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

int         le_assing_quotes(t_lexer *lexer, char *string, int index)
{
        int     end_index;
    int     length;
    int     compteur;
    char     *quotes;
    t_tokenization  *curr;

    end_index = le_find_word(string, index);
    length = end_index - index;
    quotes = (char *)malloc(sizeof(char) * length + 1);
    if (quotes == NULL)
        return (-1);
    compteur = 0;
    while (compteur != length)
    {
        quotes[compteur] = string[index + compteur];
        compteur++;
    }
    quotes[length + 1] = '\0';
    lexer = ft_add_token(lexer);
    curr = le_last_node(lexer);
    curr->type = QUOTES;
    curr->value = ft_strdup(quotes);
    free(quotes);
    return(end_index + 1);

}

int         le_assing_synbols(t_lexer *lexer, char *string, int index)
{
    int             end_index;
    char            *synbol;
    t_tokenization  *curr;

    end_index = le_identify_synbols(string, index);
    synbol = (char *)malloc(sizeof(char) * (end_index - index) + 1);
    lexer = ft_add_token(lexer);
    curr = le_last_node(lexer);

    return (end_index);
}