/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:02:37 by bchallat          #+#    #+#             */
/*   Updated: 2025/03/03 14:25:22 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_cmd	t_cmd;
typedef struct s_redirect	t_redirect;

typedef struct s_redirect
{
	t_token_type	type;
	char		**file;
	t_redirect	*next;
}	t_redirect;

typedef struct s_cmd
{
	char		**argument;
	t_redirect	*redirect;
	t_cmd		*next;
}				t_cmd;

typedef struct	s_parser
{
	int			size;
	t_cmd		*top;
}				t_parser;

//==================== parsing.c =====================*/

t_lexer     	*parsing_valid_lexer(t_lexer *lexer);
int		pars_quote(t_lexer *lexer);
t_lexer		*parse_index_lexer(t_lexer *lexer);

//====================================================*/

//=============== make_element_struct.c ==============*/

t_parser	*parse_make_parser(t_parser *parse);
t_cmd		*parse_make_command(t_cmd *cmd);
t_redirect	*parse_make_redirect(t_redirect *redirect);

//====================================================*/

//=============== free all element ===================*/

void	free_all_parser(t_parser *parser);
void	free_all_command(t_cmd *cmd);
void	free_all_redirect(t_redirect *redirect);

//====================================================*/
	
//================ rules_gramar.c ====================*/

t_token	*parse_simple_cmd(t_token *node);
t_token	*parse_cmd_list(t_token *node);
t_token	*parse_commande(t_token *node);
t_token	*parse_redirection_list(t_token *node);
t_token	*parse_redirection(t_token *node);

//====================================================*/

t_cmd	*last_command(t_parser *parse);
int	node_is_redirect(t_token *node);
int	parse_find_arrlen(t_token *node);
#endif
