/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:44:37 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/26 22:05:10 by qupollet         ###   ########.fr       */
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
	char		**envp;
}	t_exec;

typedef struct s_pipeline
{
	pid_t		*pid_tab;
	int			pipe_in[2];
	t_cmd		*cmd;
	int			pipe_out[2];
	t_pipeline	*next;
}	t_pipeline;

typedef struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
}	t_env;

// exec.c //
int			exec_main(t_parser *parser, char **envp);

// mem_utils.c //
void		ft_free_pipeline(t_pipeline *pipeline);

// find_exec.c //
int			ft_find_in_envp(char **filename, char **envp);

// builtins //
//int			mini_cd(char **args);
//void		mini_echo(char **args);
//int			mini_env(char **envp);
//int			mini_exit(char **args);
//int			mini_export(char **args, char **envp);
//int			mini_pwd(void);
//int			mini_unset(char **args, char **envp, char **n_envp);

// exec_case1.c //
//int			ft_case_one(t_parser *parser, char **envp);

// env_var.c //
//int			exec_replace_env_var(char **str);

// utils.c //
//pid_t		*ft_create_pid_tab(int table_size);
//int			**ft_create_pipe_tab(int table_size);
//void		ft_free_pipe(int **pipe_tab);
//void		ft_freetab(char **args);
//void		exec_freeall(pid_t *pid_tab, int **pipe_tab);

// buildin utils //
//int			unset_is_name_valid(const char *name);
//int			get_first_occ(char *str, char c);
//int			unset_get_tab_size(char **envp);

// builtin //
//int			mini_cd(char **args);
//int			mini_pwd(void);

// file_management.c //
//int			ft_open_file(char *file, t_token_type type);
//int			ft_checkprog(char *prog);

// exec_redirect.c //
//void		ft_print_errors(char *filename);
//int			ft_redirects(t_cmd *cmd, int *p1, int *p2);
//int			ft_redirect_input(t_cmd *cmd);

// exec_utils.c //
//void		ft_close_all_pipes(int **pipe_tab, int nb_child);
//void		ft_close_pipe(int *pipe, int read, int write);
//int			ft_has_redirect(t_cmd *cmd, t_token_type type_search);
//int			ft_exec_builtin(t_cmd *cmd, char **envp);
//int			ft_is_builtin(const char *str);

#endif