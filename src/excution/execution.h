/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:37:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/18 13:43:23 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#   define EXECUTION_H

# include "../../includes/minishell.h"

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
#endif