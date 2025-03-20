/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testeur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:06:02 by bchallat          #+#    #+#             */
/*   Updated: 2025/03/04 21:40:21 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTEUR_H
# define TESTEUR_H

#include "../../includes/minishell.h"

void		print_lexer(t_lexer *lexer);
char		*print_enum(int nb);
void		test_mi_lexer(char *string);

void		test_mi_parse(t_lexer *lexer, char *string);
void		print_parse(t_parser *parse);

int		mini_export(char **argument, char ***var_env);
void		print_env_array(char **var_env);
char		**cp_array_env(char **envp, int length);
int		ft_arrlen(char **array);
void		free_array(char **array);


#endif
