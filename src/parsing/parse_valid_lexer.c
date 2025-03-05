/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_valid_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:38:35 by bchallat          #+#    #+#             */
/*   Updated: 2025/03/05 09:02:04 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../../includes/minishell.h"

static int	valid_quote(t_lexer *lexer);
static int	valid_pipe(t_lexer *lexer);

int	parsing_valid_lexer(t_lexer *lexer)
{
    if (valid_quote(lexer) || valid_pipe(lexer))
        return (-1);
    return (0);
}

static int valid_quote(t_lexer *lexer)
{
    t_token	*curr;
    int		d_quote;
    int		s_quote;

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
    while (curr != NULL)
    {
        if (curr->type == PIPE && (prev == NULL || curr->next == NULL))
            return (1);
        if (curr->type == PIPE && curr->next->type == PIPE)
            return (1);
        prev = curr;
        curr = curr->next;
    }
    return (0);
}
