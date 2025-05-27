/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:44:37 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/28 00:26:38 by qupollet         ###   ########.fr       */
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
}	t_exec;

typedef struct s_pipeline
{
	pid_t		*pid;
	int			pipe_in[2];
	t_cmd		*cmd;
	int			pipe_out[2];
	t_pipeline	*next;
}	t_pipeline;

// exec.c //
int			exec_main(t_parser *parser, t_env *env);

// pipeline.c //
t_pipeline	*ft_create_pipeline(int nb, t_cmd *cmd);

// exec_utils.c //
void		ft_print_errors(char *src);
int			is_builtin(char *cmd);

// file_management.c //
int			file_write(char *file, t_token_type type);

// redirect.c //
int			search_redirect(t_cmd *cmd, t_token_type type);

// env.c //
t_env		*ft_create_tenv(char **envp);
int			ft_add_to_env(t_env *top, char *key, char *val);

// exec_one.c //
int			exec_one(t_cmd *cmd, t_env *env);

// find_in_path.c //
int			ft_find_in_path(char *file, t_env *env, char **res);

// builtins //
//int			mini_cd(char **args);
//void		mini_echo(char **args);
//int			mini_env(char **envp);
//int			mini_exit(char **args);
//int			mini_export(char **args, char **envp);
//int			mini_pwd(void);
//int			mini_unset(char **args, char **envp, char **n_envp);

// env_var.c //
//int			exec_replace_env_var(char **str);

// utils.c //
//pid_t		*ft_create_pid_tab(int table_size);
//int			**ft_create_pipe_tab(int table_size);
//void		ft_free_pipe(int **pipe_tab);
//void		ft_freetab(char **args);
//void		exec_freeall(pid_t *pid_tab, int **pipe_tab);

#endif