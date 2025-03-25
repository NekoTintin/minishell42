/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:02:10 by qupollet          #+#    #+#             */
/*   Updated: 2025/03/25 15:15:01 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	var_get_size(char *str)
{
	int		idx;
	int		size;
	char	*value;

	idx = -1;
	size = 0;
	while (str[++idx])
	{
		if (str[idx] != '$')
			size++;
		else
		{
			value = ft_substr()
		}
	}
	return (0);
}

int	exec_replace_env_var(char **str, char **envp)
{
	
}
