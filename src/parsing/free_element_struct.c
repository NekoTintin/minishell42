/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_element_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benoitchallat <benoitchallat@student.42.fr +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:47:09 by benoitchallat     #+#    #+#             */
/*   Updated: 2025/03/03 16:47:40 by benoitchallat    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	free_all_parser(t_parser *parser);
void	free_all_command(t_cmd *cmd);
void	free_all_redirect(t_redirect *redirect);
