/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 18:44:37 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/24 03:40:39 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

// exec.c //
int			exec_main(t_parser *parser);

// find_exec.c //
char		*ft_find_exec_in_envp(char *prog, char **envp);

// utils.c //
pid_t		*ft_create_pid_tab(int table_size);
int			**ft_create_pipe_tab(int table_size);
void		ft_free_pipe(int **pipe_tab);
void		ft_freetab(char **args);

// builtins //
int			mini_cd(char *link);
void		mini_echo(char **args);
int			mini_env(char **envp);
void		mini_exit(void);
void		mini_export(void);
int			mini_pwd(void);
void		mini_unset(void);

#endif