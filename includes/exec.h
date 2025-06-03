/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:44:37 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/04 01:35:32 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct s_pipeline	t_pipeline;
typedef struct s_env		t_env;

typedef struct s_exec
{
	int			nb_child;
	t_pipeline	*top;
	t_env		*env;
	int			**pipe_tab;
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
int			exec_builtin_solo(t_cmd *cmd, t_env *env, int type);
int			is_builtin(char *cmd);
int			exec_builtin(t_cmd *cmd, t_env *env, int builtin_code);

// exec.c //
int			exec_main(t_parser *parser, t_env *env);

// structs_init.c //
void		free_exec(t_exec *exec);
void		pipeline_free(t_pipeline *top);
t_pipeline	*ft_create_pipeline(int nb, t_cmd *cmd, t_exec *exec);

// exec_init.c //
void		free_int_tab(int **tablo, int size);
int			close_all_pipes(int **tablo, int size);
t_exec		*exec_init(int child, t_cmd *cmd, t_env *env);

// exec_utils.c //
char		**rm_whitespace_tab(char **tablo);
void		ft_print_errors(char *src, int type);
void		exec_quit(t_parser *parse, t_exec *exec);

// file_management.c //
int			file_read(char *file);
int			file_write(char *file, t_token_type type);
int			check_exec(char *exec);

// redirect.c //
int			search_redirect(t_cmd *cmd, t_token_type type);
int			ft_redirects(t_cmd *cmd, int p1, int p2);

// env.c //
t_env		*ft_create_tenv(char **envp);
int			ft_add_to_env(t_env *top, char *key, char *val);

// exec_one.c //
int			exec_restore_stdfd(int fd_in, int fd_out);
int			exec_one(t_cmd *cmd, t_env *env);

// find_in_path.c //
int			ft_find_in_path(char **file, t_env *env);

// builtins //
int			mini_cd(char **args, t_env *env);
void		mini_echo(char **args);
int			mini_env(t_env *env);
//int			mini_exit(char **args);
//int			mini_export(char **args, char **envp);
int			mini_pwd(void);
//int			mini_unset(char **args, char **envp, char **n_envp);

#endif