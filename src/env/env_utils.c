/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:53:44 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/04 02:06:45 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_env_size(t_env *env)
{
	int		size;
	t_env	*cur;

	if (!env)
		return (0);
	size = 0;
	cur = env;
	while (cur)
	{
		size++;
		cur = cur->next;
	}
	return (size);
}

void	free_tab(char **tablo)
{
	int			i;

	if (!tablo)
		return ;
	i = 0;
	while (tablo[i])
	{
		free(tablo[i]);
		i++;
	}
	free(tablo);
}
