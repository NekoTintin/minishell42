/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 04:17:08 by qupollet          #+#    #+#             */
/*   Updated: 2025/03/17 04:25:22 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

int	unset_is_name_valid(const char *name)
{
	int		idx;

	if ((name[0] < 'A' || name[0] > 'Z')
		&& (name[0] < 'a' || name[0] > 'z')
		&& name[0] != '_')
		return (0);
	idx = 1;
	while (name[idx])
	{
		if ((name[idx] < 'A' || name[idx] > 'Z')
			&& (name[idx] < 'a' || name[idx] > 'z')
			&& (name[idx] < 0 || name[idx] > 9)
			&& name[idx] != '_')
			return (0);
		idx++;
	}
	return (1);
}

int	get_first_occ(char *str, char c)
{
	int		idx;

	idx = 0;
	while (str[idx])
	{
		if (str[idx] == c)
			return (idx);
		idx++;
	}
	return (-1);
}

int	unset_get_tab_size(char **envp)
{
	int		idx;

	idx = 0;
	while (envp[idx])
		idx++;
	return (idx);
}
