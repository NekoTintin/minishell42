/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_things.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 02:58:11 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/12 03:02:27 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../../includes/minishell.h"

void	ft_free_table(char **table)
{
	if (table == NULL)
		return ;
	while (*table != NULL)
	{
		free(*table);
		*table = NULL;
		table++;
	}
}

void	ft_free_all_tabs(t_cmd *cur)
{
	if (cur->infile)
	{
		ft_free_table(cur->infile);
		free(cur->infile);
	}
	if (cur->outfile)
	{
		ft_free_table(cur->outfile);
		free(cur->outfile);
	}
	if (cur->args)
	{
		ft_free_table(cur->args);
		free(cur->args);
	}
	if (cur->append)
		free(cur->append);
}

void	ft_free_parser(t_parser *parser)
{
	t_cmd		*cur;
	t_cmd		*next;

	if (!parser)
		return ;
	cur = parser->top;
	while (cur)
	{
		ft_free_all_tabs(cur);
		next = cur->next;
		free(cur);
		cur = next;
	}
	free(parser);
}
