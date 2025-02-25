/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_valid_lexer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:38:35 by bchallat          #+#    #+#             */
/*   Updated: 2025/02/25 15:41:17 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../../includes/minishell.h"

static int      valid_quote(t_lexer *lexer);
static int      valid_pipe(t_lexer *lexer);

t_lexer     *parsing_valid_lexer(t_lexer *lexer)
{
    if (valid_quote(lexer) || valid_pipe(lexer))
        return (ll_free_lexer(lexer), NULL);
    return (lexer);
}

static int      valid_quote(t_lexer *lexer)
{
    t_token     *curr;
    int         d_quote;
    int         s_quote;

    curr = lexer->header;
    d_quote = 0;
    s_quote = 0;
    while (curr != NULL)
    {
        if (curr->type == D_QUOTES && d_quote == 0 && s_quote == 0)
            d_quote += 1;
        else if (curr->type == D_QUOTES && d_quote != 0 && s_quote == 0)
            d_quote -= 1;
        else if (curr->type == S_QUOTES && s_quote == 0 && d_quote == 0)
            s_quote += 1;
        else if (curr->type == S_QUOTES && s_quote != 0 && d_quote == 0)
            s_quote -= 1;
        curr = curr->next;
        //printf("s_quote: %d & d_quote : %d\n", s_quote, d_quote);
    }
    if (d_quote != 0 || s_quote != 0)
        return (1);
    return (0);
}

static int      valid_pipe(t_lexer *lexer)
{
    t_token *curr;
    t_token *prev;

    prev = NULL;
    curr = lexer->header;
    printf("start loop\n");
    while (curr != NULL)
    {
        if (curr->type == PIPE && (prev == NULL || curr->next == NULL))
            return (1);
        printf("int loop\n");
        prev = curr;
        curr = curr->next;
    }
    printf("end loop\n");
    return (0);
}