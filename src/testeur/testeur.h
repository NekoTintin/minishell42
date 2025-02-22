/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testeur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:06:02 by bchallat          #+#    #+#             */
/*   Updated: 2025/02/22 14:15:51 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTEUR_H
# define TESTEUR_H

#include "../../includes/minishell.h"

void            print_lexer(t_lexer *lexer);
char            *print_enum(int nb);
t_lexer         *test_mi_lexer(char *string, t_lexer *lexer);

#endif