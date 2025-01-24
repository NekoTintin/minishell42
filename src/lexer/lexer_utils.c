/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:48:04 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/24 02:12:06 by unbuntu          ###   ########.fr       */
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

t_lexer    *ft_add_token(t_lexer *lexer)
{
    t_lexer            *current;
    t_tokenization     *new_node;
    
    current = le_last_node(lexer);
    new_node = ft_init_tolken(new_node);
    if(new_node = NULL)
        return (NULL);
    current->header->next = new_node;
    lexer->size++;
    return (lexer);
}

t_tokenization   *le_last_node(t_lexer *lexer)
{
    t_lexer    *current;
    current = lexer;
    while (current->header != NULL)
        current->header = current->header->next;
    return (current->header);
}