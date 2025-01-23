/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 20:25:00 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/23 22:22:54 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static int      le_isspace(const char *c);
static void     le_handle_quotes(void);
//static t_token_type     le_identify_synbols(t_tokenization *tolken);
static void     le_variable_env(void);

t_lexer    *lexer_to_tolken(const char *string_readline)
{

    t_lexer *lexer; // tete de ma list
    int     index;  // index pour parcourir la chaine de caractere
    //init list; 
    //loop pour parcourir la liste jusqua tomber sur \0 
        //condition if si pas un espace
            //regarder ca longeur et si 1 ou 2 
        //condition si espace tokeniser 
        //incremantation index
    
    //decouper la chaine avec les espace 
    //associer chaque element a un token 
}

static int      le_isspace(const char *c)
{
    if (c == 32)
        return (1);
    return (0);
}

static t_token_type     le_identify_synbols(t_tokenization *tolken)
{
    char    *str;

    str = tolken->value;
    if (str[0] == '|')
        tolken->type = PIPE;
    if (str[0] == '<')
    {
        if (str[0] == '<' && str[1] == '<')
            tolken->type = REDIRECT_IN;
        tolken->type = HEREDOC;
    }
    if (str[0] == '>')
    {
        if (str[0] == '>' && str[1] == '>')
            tolken->type = REDIRECT_OUT;
        tolken->type = APPEND;
    }
    tolken->type = UNKNOWN;
}
