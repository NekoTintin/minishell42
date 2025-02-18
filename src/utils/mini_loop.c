/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:25 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/18 10:29:40 by bchallat         ###   ########.fr       */
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
    if (string == NULL)
        return (EXIT_SUCCESS);
    printf("Test : %s\n", string);
    if (lexer == NULL)
        return (ll_free_lexer(lexer),EXIT_SUCCESS);
    print_chain(lexer);
    ll_free_lexer(lexer);
    return (1);
}