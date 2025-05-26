/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:57:23 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/20 20:11:35 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "minishell.h"

// Déclaration anticipée de `t_tokenization`
typedef struct s_token	t_token;

typedef enum e_token_type
{
	WORD,
	VAR_ENV,
	S_QUOTES,
	D_QUOTES,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	APPEND,
	HEREDOC,
	WHITESPACE,
	UNKNOWN
}	t_token_type;

typedef struct s_token
{
	int		index;
	char		*value;
	t_token_type	type;
	t_token		*next;
}	t_token;

typedef struct s_lexer
{
	int				size;
	t_token			*header;
}	t_lexer;

t_lexer		*mi_make_lexer(char *readline_string);

//==================== chain_list.c =====================*/

t_lexer		*ll_init_lexer(t_lexer *lexer);
t_token		*ll_init_tolken(t_token *token);
t_lexer		*ll_add_token(t_lexer *lexer);
t_token		*ll_last_token(t_lexer *lexer);
void		ll_free_lexer(t_lexer *lexer);

//=======================================================*/

//==================== lexer_utils.c ==================*/

int			lx_space_token(int index, t_lexer *lexer);
int			lx_value_node(int index, char *string, t_lexer *lexer);

//======================================================/

//==================== tokenization.c ===================*/

int			lx_assing_quotes(t_token *node);
int			lx_assing_word(t_token *node);
int			lx_assing_synbols(t_token *node);
int			lx_assing_env(t_token *node);

//=======================================================*/

//=======================================================*/

t_lexer		*lx_clean_lexer(t_lexer *lexer);

//=======================================================*/
#endif
