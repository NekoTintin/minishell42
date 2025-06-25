/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:01:22 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/24 13:32:12 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

# define ERORR "bash: erreur de syntaxe près du symbole inattendu «"

typedef struct s_cmd		t_cmd;
typedef struct s_redirect	t_redirect;

typedef struct s_redirect
{
	t_token_type	type;
	char			**file;
	t_redirect		*next;
}	t_redirect;

typedef struct s_cmd
{
	char		**argument;
	t_redirect	*redirect;
	char		*heredoc;
	t_cmd		*next;
}				t_cmd;

typedef struct s_parser
{
	int			size;
	t_cmd		*top;
}				t_parser;

t_parser	*mi_make_parse(t_parser *parse, t_lexer *lexer);

//==================== parsing.c =====================*/

int			parsing_valid_lexer(t_lexer *lexer);
t_lexer		*parse_conc_quote(t_lexer *lexer);

//====================================================*/

//=============== make_element_struct.c ==============*/

t_parser	*parse_make_parser(t_parser *parse);
t_cmd		*parse_make_command(t_cmd *cmd);
t_redirect	*parse_make_redirect(t_redirect *redirect);

//====================================================*/

//================ rules_gramar.c ====================*/

char		*parse_simple_cmd(t_token *node);
t_parser	*parse_cmd_list(t_token *node, t_parser *parse);
t_token		*parse_commande(t_token *node, t_cmd *cmd);
t_token		*parse_redirection_list(t_token *node, t_cmd *cmd);
t_token		*parse_redirection(t_token *node, t_redirect *redirect);

//====================================================*/

//================ parse ast utils ===================*/

t_parser	*add_command(t_parser *parse);
t_cmd		*last_command(t_parser *parse);
int			node_is_redirect(t_token *node);
int			node_is_ascii(t_token *node);
int			parse_find_arrlen(t_token *node);

//====================================================*/

//=============== free all element ===================*/

void		free_all_parser(t_parser *parser);
void		free_all_command(t_cmd *cmd);
void		free_all_redirect(t_redirect *redirect);

//====================================================*/

int			parse_herdoclen(t_token *node);
t_redirect	*last_redirect(t_cmd *cmd);
t_cmd		*parse_add_redirect(t_cmd *cmd);
t_token		*parse_redirection_herdoc(t_token *node, t_redirect *redirect);

#endif
