/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:01:22 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/12 01:05:55 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../includes/minishell.h"
# include <linux/limits.h>
# include "parsing.h"

typedef struct s_cmd	t_cmd;

typedef struct s_cmd
{
	char		**args;
	char		**infile;
	char		**outfile;
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
t_parser			*parsing(t_lexer *lexer);

//==================== init_parser.c =====================*/
t_parser			*ft_init_parser(void);
t_cmd				*ft_parser_last(t_parser *parser);
int					ft_init_command(t_parser *parser);
void				ft_free_parser(t_parser *parser);

//==================== pars_utils.c =====================*/
int					ft_command_counter(t_lexer *lexer);
char				*ft_get_from_env(char *env_var, char **envp);
int					ft_get_symbol(t_token *token);

//==================== parser_handle.c ===================*/
int					ft_add_arg(char ***table, char *arg);
int					ft_add_to_append(int **table, int value);
int					ft_handle_symbol(t_token *token, t_cmd *cmd);
int					ft_handle_word(t_token *token, t_cmd *cmd);

//==================== parser_utils.c ===================*/
int					ft_is_builtin(const char *str);

#endif