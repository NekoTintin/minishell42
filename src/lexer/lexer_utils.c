/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:48:04 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/23 23:06:36 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer    *ft_init_lexer(t_lexer *lexer)
{
    lexer = (t_lexer *)malloc(sizeof(t_lexer));
    if (lexer ==  NULL)
        return(NULL);
    lexer->header = NULL;
    lexer->size = 0;
    return (lexer);
}

void    ft_free_lexer(t_lexer *lexer)
{
    t_tokenization  *free_node;
    while (lexer->header != NULL)
    {
        free_node = lexer->header;
        lexer->header = lexer->header->next;
        free(free_node->value);
        free(free_node);
    }
    free(lexer);
}

t_tokenization    *ft_init_tolken(t_tokenization *token)
{
    t_tokenization  *node;
    int             size;
    node = (t_tokenization *)malloc(sizeof(t_tokenization));
    if (node == NULL)
        return (NULL);
    node->value = NULL;
    node->next = NULL;
    node->type = UNKNOWN;
    return(node);
}

t_lexer    *ft_add_token(t_lexer *lexer, char *string)
{
    t_lexer            *current;
    t_tokenization     *new_node;
    
    current = lexer;
    while (current->header != NULL)
        current->header = current->header->next;
    new_node = ft_init_tolken(new_node);
    if(new_node = NULL)
        return (NULL);
    new_node->type = ft_strdup(string);
    if(new_node->type == NULL)
    {
        free(new_node);
        return(NULL);
    }
    current->header->next = new_node;
    lexer->size++;
    return (lexer);
}