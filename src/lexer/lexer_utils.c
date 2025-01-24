/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:48:04 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/24 10:04:42 by unbuntu          ###   ########.fr       */
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

t_tokenization    *ft_init_tolken(t_tokenization *node)
{   
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
    t_tokenization     *curr;
    t_tokenization     *node;
    
    node = ft_init_tolken(node);
    node->next = lexer->header;
    lexer->header = node;
    lexer->size += 1;
    return (lexer);

}

t_tokenization   *le_last_node(t_lexer *lexer)
{
    t_tokenization    *current;
    
    current = lexer->header;
    if(current == NULL)
        return (current);
    while (current->next != NULL)
        current = current->next;
    return (current);
}