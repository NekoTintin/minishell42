/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:26:46 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/17 15:06:23 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
#   define BUILTIN_H

#include "minishell.h"

int mini_cd(char *link);
void mini_echo(char **args);
int mini_env(char **envp);
void mini_exit(void);
void mini_export(void);
int mini_pwd(void);
void mini_unset(void);

#endif