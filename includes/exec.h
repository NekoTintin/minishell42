/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:44:37 by qupollet          #+#    #+#             */
/*   Updated: 2025/03/08 19:06:49 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

// exec.c //
int			exec_main(t_parser *parser, char **envp);

// find_exec.c //
int			ft_find_in_envp(char **filename, char **envp);

// utils.c //
pid_t		*ft_create_pid_tab(int table_size);
int			**ft_create_pipe_tab(int table_size);
void		ft_free_pipe(int **pipe_tab, int tab_size);
void		ft_freetab(char **args);

// builtins //
int			mini_cd(char **args);
void		mini_echo(char **args);
int			mini_env(char **envp);
void		mini_exit(void);
void		mini_export(void);
int			mini_pwd(void);
void		mini_unset(void);

// file_management.c //
int			ft_check_open_file(char *file, t_token_type type);
int			ft_checkprog(char *prog);

// exec_redirect.c //
int			ft_exec_input(t_cmd *cmd);
int			ft_exec_output(t_cmd *cmd);

// exec_utils.c //
int			ft_is_builtin(const char *str);

#endif