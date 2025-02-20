/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:25 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/27 14:51:45 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int    mini_loop(t_tools *tools);
int    reset_mini_loop(t_tools *tools);

int    mini_loop(t_tools *tools)
{
    char    *string;
    t_lexer *lexer;

    string = readline(tools->prompt);
    lexer = mi_make_lexer(string);
    if (string == NULL)
        exit(EXIT_SUCCESS);

    reset_mini_loop(tools);
    ll_free_lexer(lexer);
    return (1);
}

int reset_mini_loop(t_tools *tools)
{
    mini_loop(tools);
    return(1);
}