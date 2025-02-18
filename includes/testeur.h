/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testeur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:37:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/18 21:16:35 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTEUR_H
#   define TESTEUR_H

# include "minishell.h"

typedef struct s_cmd	t_cmd;
typedef	struct s_parser		t_parser;

typedef struct s_cmd
{
	char		**args;
	char		**infile;
	char		**outfile;
	int			*append;
	int			is_builtin;
	t_cmd		*next;
}				t_cmd;

typedef struct s_parser
{
	int			size;
	t_cmd		*top;
}				t_parser;

/*===================== execution.c ====================*/

int mi_execution(t_parser *parser);

/*======================================================*/

/*====================== Builtin =======================*/

int     mini_cd(char *link);
void    mini_echo(char **args);
int     mini_env(char **envp);
void    mini_exit(void);
void    mini_export(void);
int     mini_pwd(void);
void    mini_unset(void);

/*======================================================*/
#endif