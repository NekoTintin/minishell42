/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:57:23 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/23 22:45:01 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef enum e_token_type {
    WORD,
    PIPE,
    REDIRECT_IN,
    REDIRECT_OUT,
    APPEND,
    HEREDOC,
    WHITESPACE,
    UNKNOWN
} t_token_type;

typedef struct s_tools
{
    const char  *prompt;
    t_lexer     *lexer;
    
} t_tools;

typedef struct s_lexer
{
    t_tokenization *header;
    int             size;
}   t_lexer;

typedef struct s_tokenization
{
    char            *value;  // La valeur du token
    t_token_type     type;    // Type du token (mot, symbole, ect) (voir macro)
    t_tokenization  *next;   // on lie les token dans l ordre

}   t_tokenization;

int    mini_loop(t_tools *tools);