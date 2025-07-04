/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:44:37 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/28 17:33:53 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

# ifndef LLG_MAX
#  define LLG_MAX 9223372036854775807LL
# endif

typedef struct s_pipeline	t_pipeline;
typedef struct s_env		t_env;
typedef struct s_minishell	t_minishell;

typedef struct s_exec
{
	int				nb_child;
	t_pipeline		*top;
	t_env			*env;
	int				**pipe_tab;
	t_minishell		*mini;
}	t_exec;

typedef struct s_pipeline
{
	int			id;
	pid_t		pid;
	t_cmd		*cmd;
	t_pipeline	*next;
	t_exec		*exec;
}	t_pipeline;

// builtins.c //
int			exec_builtin_solo(t_cmd *cmd, t_parser *parse, t_exec *exec,
				int type);
int			is_builtin(char *cmd);
int			exec_builtin(t_cmd *cmd, t_parser *parse,
				t_exec *exec, int builtin_code);
int			exec_builtin_pipeline(t_cmd *cmd, t_parser *parse,
				t_exec *exec, int type);
// exec.c //
int			exec_main(t_parser *parser, t_env *env, t_minishell *mini);

// structs_init.c //
void		free_exec(t_exec *exec);
void		pipeline_free(t_pipeline *top);
t_pipeline	*ft_create_pipeline(int nb, t_cmd *cmd, t_exec *exec);

// exec_init.c //
void		free_int_tab(int **tablo, int size);
int			close_all_pipes(int **tablo, int size);
t_exec		*exec_init(int child, t_cmd *cmd, t_env *env, t_minishell *mini);

// exec_utils.c //
char		**rm_whitespace_tab(char **tablo);
void		ft_print_errors(char *src, int type);
void		exec_quit(t_parser *parse, t_exec *exec);

// file_management.c //
int			file_read(char *file);
int			file_write(char *file, t_token_type type);
int			heredoc_file(t_cmd *cmd);
int			check_exec(char *exec);

// redirect.c //
int			ft_redirects(t_cmd *cmd, int p1, int p2);

// redirect_utils.c //
int			search_red(t_cmd *cmd, t_token_type type);
void		free_heredoc(t_cmd *top);
int			redir_prepare(t_parser *parse, t_exec *exec);

// env.c //
t_env		*ft_create_tenv(char **envp);
int			ft_add_to_env(t_env *top, char *key, char *val);

// exec_one.c //
int			exec_restore_stdfd(int fd_in, int fd_out);
int			exec_one(t_cmd *cmd, t_parser *parse, t_exec *exec);

// find_in_path.c //
int			ft_find_in_path(char **file, t_env *env);

// redirect_heredoc.c //
int			exec_heredoc(t_cmd *cmd);
int			pipeline_read_all_heredoc(t_cmd *cmd);

// utils.c //
void		print_code(int code);
int			ft_check_find_in_path_path(t_env *env, char **file);

// builtins //
int			mini_cd(char **args, t_env *env);
void		mini_echo(char **args);
int			mini_env(t_env *env);
int			mini_exit(char **args, t_parser *parse, t_exec *exec);
int			mini_exit_for_children(char **args);
int			mini_export(char **argument, t_env *env);
char		**m_exp_tab(char **args);
int			mini_pwd(void);
int			mini_unset(char **args, t_env *env);

#endif