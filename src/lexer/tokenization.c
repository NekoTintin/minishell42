/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:25:00 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/24 05:51:42 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char    *ft_strndup(const char *s1, size_t n);
static t_tokenization     *le_conditional_assing(t_tokenization *curr, char *str, t_token_type type, int length);

int         le_assing_word(t_lexer *lexer, char *string, int index)
{
    int     end_index;
    int     length;
    t_tokenization  *curr;

    end_index = le_find_word(string, index);
    length = end_index - index;
    lexer = ft_add_token(lexer);
    curr = le_last_node(lexer);
    curr = le_conditional_assing(curr, string[index], WORD, length);
    return(end_index + 1);
}

int         le_assing_quotes(t_lexer *lexer, char *string, int index)
{
    int     end_index;
    int     length;
    t_tokenization  *curr;

    end_index = le_find_word(string, index);
    length = end_index - index;
    lexer = ft_add_token(lexer);
    curr = le_last_node(lexer);
    curr = le_conditional_assing(curr, string[index], QUOTES, length);
    return(end_index + 1);
}

int         le_assing_synbols(t_lexer *lexer, char *string, int index)
{
    int             end_index;
    t_tokenization  *curr;

    end_index = le_identify_synbols(string, index);
    lexer = ft_add_token(lexer);
    curr = le_last_node(lexer);
    if (end_index - index == 2)
    {
        if (string[index] == '<')
            curr = le_conditional_assing(curr, string[index], REDIRECT_IN, end_index - index);
        if (string[index] == '>')
            curr = le_conditional_assing(curr, string[index], REDIRECT_OUT, end_index - index);
    }
    else if (string[index] == '<')
            curr = le_conditional_assing(curr, string[index], HEREDOC, end_index - index);
    else if (string[index] == '>')
            curr = le_conditional_assing(curr, string[index], APPEND, end_index - index);
    else if (string[index] == '|')
            curr = le_conditional_assing(curr, string[index], PIPE, end_index - index);
    return (end_index);
}

int         le_assing_env(t_lexer *lexer, char *string, int index)
{
    
}

static t_tokenization     *le_conditional_assing(t_tokenization *curr, char *str, t_token_type type, int length)
{
        curr->value = ft_strdnup(str, length);
        if (curr->value != NULL)
            return(NULL);
        curr->type = type;
        return (curr);
}

static char    *ft_strndup(const char *s1, size_t n)
{
    char    *dup;
    size_t  i;

    i = 0;
    while (s1[i] && i < n)
        i++;
    dup = (char *)malloc(sizeof(char) * (i + 1)); // +1 pour le '\0'
    if (!dup)
        return (NULL);
    i = 0;
    while (s1[i] && i < n)
    {
        dup[i] = s1[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}

/*
int         le_assing_synbols(t_lexer *lexer, char *string, int index)
{
    int             end_index;
    char            *synbol;
    t_tokenization  *curr;

    end_index = le_identify_synbols(string, index);
    synbol = (char *)malloc(sizeof(char) * (end_index - index) + 1);
    lexer = ft_add_token(lexer);
    curr = le_last_node(lexer);
    if (end_index - index == 2)
    {
        if (string[index] == '<')
            curr = le_conditional_assing(curr, string[index], REDIRECT_IN, end_index - index);
        if (string[index] == '>')
            curr = le_conditional_assing(curr, string[index], REDIRECT_OUT, end_index - index);
    }
    else if (string[index] == '<')
            curr = le_conditional_assing(curr, string[index], HEREDOC, end_index - index);
    else if (string[index] == '>')
            curr = le_conditional_assing(curr, string[index], APPEND, end_index - index);
    else if (string[index] == '|')
            curr = le_conditional_assing(curr, string[index], PIPE, end_index - index);
    return (end_index);
}
*/

/*
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
*/

/*
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
*/