/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:01:22 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/20 20:17:58 by qupollet         ###   ########.fr       */
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
t_parser			*parsing(t_lexer *lexer, char **envp);

//==================== init_parser.c =====================*/
t_parser			*ft_init_parser(void);
t_cmd				*ft_parser_last(t_parser *parser);
int					ft_init_command(t_parser *parser);
void				ft_free_parser(t_parser *parser);

//==================== pars_utils.c =====================*/
int					ft_command_counter(t_lexer *lexer);
int					ft_get_symbol(t_token *token);
int					remove_quotes(t_token *token);
int					ft_is_builtin(const char *str);

//==================== parser_handle.c ===================*/
int					ft_add_arg(char ***table, char *arg);
int					ft_add_to_append(int **table, int value);
int					ft_handle_symbol(t_token *token, t_cmd *cmd);
int					ft_handle_word(t_token *token, t_cmd *cmd, char **envp);

//==================== env_var_handle.c ===================*/
char				*check_if_exist(char *env, char **envp);
int					ft_replace_env(t_token *token, char **envp);

//==================== env_var_utils.c ===================*/
int					ft_custom_strlen(char *str);
char				*get_env_value(char *str, char **envp);

#endif