/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:02:37 by bchallat          #+#    #+#             */
/*   Updated: 2025/02/26 12:54:41 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct s_cmd	t_cmd;

typedef struct s_cmd
{
	char		**args;
	char		**infile;
	char		**outfile;
	char		*delimiter;
	int			delete_tabs;
	int			*append;
	int			is_builtin;
	t_cmd		*next;
}				t_cmd;

typedef struct s_parser
{
	int			size;
	t_cmd		*top;
}				t_parser;

//==================== parsing.c =====================*/

t_lexer     *parsing_valid_lexer(t_lexer *lexer);

//====================================================*/

//==================== struct_ast.c =====================*/

t_parser    *pars_make_ast(t_parser *ast);
t_cmd       *pars_make_cmd(t_cmd *cmd);
void    	pars_free_ast(t_parser *ast);
void    	pars_free_cmd(t_cmd *cmd);
void    	pars_free_arr(char **arr);

//====================================================*/

#endif