/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:48:04 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/25 18:04:11 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_lexer     *lx_dup_str(char *dup_str, t_lexer *lexer);

int     lx_space_token(int index, t_lexer *lexer)
{
    t_token     *node;

    lexer = ll_add_token(lexer);
    if(lexer == NULL)
        return (-1);
    node = ll_last_token(lexer);
    node->value = ft_strdup(" ");
    node->type = WHITESPACE;
    return (index + 1);
}

int     lx_value_node(int index, char *string, t_lexer *lexer)
{
    int    length;
    int    index_dup;
    char   *dup_str;

    length = 0;
    while (string[index + length] != '\0' && string[index + length] != 32)
        length++;

    dup_str = (char *)malloc(sizeof(char) * (length + 1));
    if (dup_str == NULL)
        return (ll_free_lexer(lexer), -1);
    
    index_dup = 0;
    while(index_dup != length)
    {
        dup_str[index_dup] = string[index + index_dup];
        index_dup++;
    }
    dup_str[index_dup] = '\0';
    lexer = lx_dup_str(dup_str, lexer);
    if(lexer == NULL)
        return (-1);
    return (index + length);
}

static t_lexer     *lx_dup_str(char *dup_str, t_lexer *lexer)
{
    t_token     *node;

    lexer = ll_add_token(lexer);
    if(lexer == NULL)
        return (NULL);
    node = ll_last_token(lexer);
    node->value = dup_str;
    return(lexer);
}