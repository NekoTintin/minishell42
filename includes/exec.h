/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:44:37 by qupollet          #+#    #+#             */
/*   Updated: 2025/03/19 17:17:29 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# define ERR_FORK "bash: fork failed: Resource temporarily unavailable"

# include "minishell.h"

// exec_case1.c //
int			ft_case_one(t_parser *parser, char **envp);

// exec.c //
int			exec_main(t_parser *parser, char **envp);

// find_exec.c //
int			ft_find_in_envp(char **filename, char **envp);

// utils.c //

int			ft_cmd_counter(t_parser *parser);
pid_t		*ft_create_pid_tab(int table_size);
int			**ft_create_pipe_tab(int table_size);
void		ft_free_pipe(int **pipe_tab, int tab_size);
void		ft_freetab(char **args);

// builtins //
int			mini_cd(char **args);
void		mini_echo(char **args);
int			mini_env(char **envp);
int			mini_exit(char **args);
int			mini_export(char **args, char **envp);
int			mini_pwd(void);
int			mini_unset(char **args, char **envp, char **n_envp);

// buildin utils //
int			unset_is_name_valid(const char *name);
int			get_first_occ(char *str, char c);
int			unset_get_tab_size(char **envp);

// builtin //
int			mini_cd(char **args);
int			mini_pwd(void);

// file_management.c //
int			ft_open_file(char *file, t_token_type type);
int			ft_checkprog(char *prog);

// exec_redirect.c //
void		ft_print_errors(char *filename);
int			ft_redirects(t_cmd *cmd, int *p1, int *p2);
int			ft_redirect_input(t_cmd *cmd);

// exec_utils.c //
void		ft_close_all_pipes(int **pipe_tab, int nb_child);
void		ft_close_pipe(int *pipe, int read, int write);
int			ft_has_redirect(t_cmd *cmd, t_token_type type_search);
int			ft_exec_builtin(t_cmd *cmd, char **envp);
int			ft_is_builtin(const char *str);

#endif