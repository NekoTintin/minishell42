/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:30:42 by bchallat          #+#    #+#             */
/*   Updated: 2025/02/24 16:50:35 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

t_parser    *mi_parsing(t_lexer *lexer)
{
    t_parser *parser;

    lexer = ps_backtrack_quote(lexer);
    lexer = ps_clean_lexer(lexer);
    
    //fonction ini parser
    return (parser);
}