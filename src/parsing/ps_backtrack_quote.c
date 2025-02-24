/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_backtrack_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:44:56 by bchallat          #+#    #+#             */
/*   Updated: 2025/02/24 18:11:48 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

static t_token *quote_token(t_token *node);
static int number_node_in_quote(t_token *node);
static t_token *make_token_quote(t_token *node, int number_node);
static void free_node_of_quote(t_token *node, int number_node);


t_lexer		*ps_bactrack_quote(t_lexer *lexer)
{
	t_token *node;
	
	node = lexer->header;
	while (node != NULL)
	{
		if (node->next->type == S_QUOTES || node->next->type == D_QUOTES)
		{
			node->next = quote_token(node);
			if (node->next == NULL)
				return (NULL);
		}
		node = node->next;
	}
}

static t_token *quote_token(t_token *node)
{
    t_token *q_node;
    int     number_node;

    number_node = number_node_in_quote(node);
    if (number_node == 0)
        return (NULL);
    q_node = make_token_quote(node, number_node);
    if(q_node == NULL || q_node->value == NULL)
        return (NULL);
    free_node_of_quote(node, number_node);
    return (q_node);
}

static int number_node_in_quote(t_token *node)
{

}

static t_token *make_token_quote(t_token *node, int number_node)
{
    t_token *q_node;
    char    *value;
    int index;
    int length;

    index = 0;
    length = 0;
    while (index != number_node)
    {
        length += ft_strlen(node->value);
        node = node->next;
        index++;
    }
    q_node = ll_init_tolken(q_node);    
    value = (char *)malloc(sizeof(char) * (length + 1));
    if(q_node == NULL || value == NULL)
        return (NULL);
    //copie des chaine ;
    return (q_node);
}

static void free_node_of_quote(t_token *node, int number_node)
{
    t_token *n_free;
    int index;

    index = 0;
    while (index != number_node)
    {
        n_free = node;
        node = node->next;
        free(n_free->value);
        free(n_free);
        index++;
    }
}
