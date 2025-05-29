/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:15:12 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/29 15:16:13 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_int_tab(int **tablo, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		free(tablo[i]);
		i++;
	}
	free(tablo);
}
