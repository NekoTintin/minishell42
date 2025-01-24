/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:57:23 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/24 06:02:55 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef enum e_token_type {
    WORD,
    QUOTES,
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

//===================== mini_loop.c =================*/

int                 mini_loop(t_tools *tools);

//======================================================/

//==================== lexer_utils.c ==================*/

void                ft_free_lexer(t_lexer *lexer);
t_lexer             *ft_init_lexer(t_lexer *lexer);
t_lexer             *ft_add_token(t_lexer *lexer);
t_tokenization      *ft_init_tolken(t_tokenization *token);
t_tokenization      *le_last_node(t_lexer *lexer);

//======================================================/

//================== tokenization_utils.c ==============*/

int    le_isspace(const char *c);
int    le_find_word(char *string, int index_of_word);
int    le_variable_env(char *string, int index_of_dollar);
int    le_identify_synbols(char *string, int index_synbols);
int    le_handle_quotes(char *string, int index_of_quotes);


//=======================================================*/

//======================== lexer.c ======================*/

t_lexer    *le_tolkenization(const char *string_readline, t_lexer *lexer);
int        le_assing_type(t_lexer *lexer, char *string, int index);

//=======================================================*/

//==================== tokenization.c ===================*/

int         le_assing_quotes(t_lexer *lexer, char *string, int index);
int         le_assing_word(t_lexer *lexer, char *string, int index);
int         le_assing_synbols(t_lexer *lexer, char *string, int index);
int         le_assing_env(t_lexer *lexer, char *string, int index);

//=======================================================*/