/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_element_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:00:34 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/03 16:01:00 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

t_parser	*parse_make_parser(t_parser *parse);
t_cmd		*parse_make_command(t_cmd *cmd);
t_redirect	*parse_make_redirect(t_redirect *redirect);


t_parser	*parse_make_parser(t_parser *parse)
{
	if (parse != NULL)
		return (NULL);
	parse = (t_parser *)malloc(sizeof(t_parser));
	if (parse == NULL)
		return (NULL);
	parse->top = NULL;
	parse->size = 0;
	return (parse);
}

t_cmd		*parse_make_command(t_cmd *cmd)
{
	if (cmd != NULL)
		return (NULL);
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->argument = NULL;
	cmd->redirect = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_redirect	*parse_make_redirect(t_redirect *redirect)
{
	if (redirect != NULL)
		return (NULL);
	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (redirect == NULL)
		return (NULL);
	redirect->type = UNKNOWN;
	redirect->file = NULL;
	redirect->next = NULL;
	return (NULL);
}
