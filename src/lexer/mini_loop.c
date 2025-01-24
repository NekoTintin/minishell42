/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:25 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/24 06:47:52 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int    mini_loop(t_tools *tools);
int    reset_mini_loop(t_tools *tools);

int    mini_loop(t_tools *tools)
{
    char    *string;

    string = readline(tools->prompt);
    if (string == NULL)
        exit(EXIT_SUCCESS);
    reset_mini_loop(tools);
    return (1);
}

int reset_mini_loop(t_tools *tools)
{
    mini_loop(tools);
    return(1);
}