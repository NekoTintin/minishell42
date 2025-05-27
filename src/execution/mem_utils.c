/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:27:07 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/26 12:28:26 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_pipeline(t_pipeline *pipeline)
{
	t_pipeline	*tmp;

	while (pipeline)
	{
		tmp = pipeline;
		pipeline = pipeline->next;
		free(tmp);
	}
}
