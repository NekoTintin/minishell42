/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:01:22 by qupollet          #+#    #+#             */
/*   Updated: 2025/01/29 12:50:04 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../../includes/minishell.h"
# include <linux/limits.h>

typedef struct s_cmd	t_cmd;

typedef struct s_cmd
{
	char		**args;
	char		*infile;
	char		*outfile;
	int			append;
	t_cmd		*next;
}				t_cmd;

typedef struct s_parser
{
	int			size;
	t_cmd		*top;
}				t_parser;

// t_command_util functions
t_parser			*ft_init_parser(void);
t_cmd				*ft_parser_last(t_parser *parser);
int					ft_init_command(t_parser *parser);
void				ft_free_parser(t_parser *parser);

#endif