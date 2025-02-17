/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:25 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/17 18:42:13 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    mini_loop(void);

int    mini_loop(void)
{
    char    *string;
    char    buffer[PATH_MAX];
    t_lexer *lexer;

    getcwd(buffer, sizeof(buffer));
    ft_printf("%s-> ", buffer);
    string = readline("");
    lexer = mi_make_lexer(string);
    if (string == NULL)
        return (ll_free_lexer(lexer), EXIT_SUCCESS);
    
    ll_free_lexer(lexer);
    return (1);
}

