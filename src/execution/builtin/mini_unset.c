/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:37:00 by bchallat          #+#    #+#             */
/*   Updated: 2025/03/17 04:32:32 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

int	unset_find_in_envp(char *var, char **envp)
{
	int			idx;
	size_t		var_len;
	int			equal_pos;

	if (!var || !envp || !envp[0])
		return (-1);
	var_len = ft_strlen(var);
	idx = 0;
	while (envp[idx])
	{
		equal_pos = get_first_occ(envp[idx], '=');
		if (equal_pos == -1)
		{
			idx++;
			continue ;
		}
		if (ft_strncmp(envp[idx], var, var_len) == 0
			&& envp[idx][var_len] == '=')
			return (idx);
		idx++;
	}
	return (-1);
}

char	**unset_create_new_envp(int idx, char **envp)
{
	char	**new_envp;
	int		j;
	int		k;

	j = 0;
	k = 0;
	new_envp = ft_calloc(unset_get_tab_size(envp), sizeof(char *));
	if (!new_envp)
		return (NULL);
	while (envp[j])
	{
		if (j != idx)
		{
			new_envp[k] = envp[j];
			k++;
		}
		j++;
	}
	new_envp[k] = NULL;
	return (new_envp);
}

int	mini_unset(char **args, char **envp, char ***n_envp)
{
	int			idx;
	int			varia_idx;
	char		**new_envp;

	if (args[1] == NULL)
		return (0);
	idx = 0;
	while (args[++idx])
	{
		if (unset_is_name_valid(args[idx]) == 0)
			continue ;
		varia_idx = unset_find_in_envp(args[idx], envp);
		if (varia_idx == -1)
			continue ;
		new_envp = unset_create_new_envp(varia_idx, envp);
		if (!new_envp)
			continue ;
		envp = new_envp;
	}
	*n_envp = envp;
	return (0);
}
