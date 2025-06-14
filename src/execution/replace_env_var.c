/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:05:03 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/13 13:11:01 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_key_from_str(char *str, int start, int idx, t_env *env)
{
	char	*key;
	char	*val;

	if (start >= idx)
		return (NULL);
	key = ft_substr(str, start, idx - start);
	val = ft_env_get_value(env, key);
	free(key);
	if (!val)
		return (NULL);
	return (val);
}

int	get_size_with_var(char *str, t_env *env)
{
	int		idx;
	int		size;
	int		start;
	char	*val;

	idx = -1;
	size = 0;
	start = 0;
	while (str[++idx])
	{
		if (str[idx] == '$')
		{
			idx++;
			start = idx;
			while (ft_isalnum(str[idx]))
				idx++;
			val = get_key_from_str(str, start, idx, env);
			if (val)
				size += ft_strlen(val);
		}
		else
			size++;
	}
	return (size);
}

int	copy_to_str(char *str, char **nstr, t_env *env)
{
	int		idx;
	int		idx_nstr;

	idx = 0;
	idx_nstr = 0;
	while (str[idx])
	{
		if (str[idx] == '$')
		{
			(void)env;
			idx++;
			// TO DO
		}
		else
			(*nstr)[idx_nstr++] = str[idx++];
	}
	return (0);
}

char	*replace_var(char *str, t_env *env)
{
	char	*nstr;
	int		size;

	if (!str || !env || !*str)
		return (NULL);
	size = get_size_with_var(str, env);
	nstr = ft_calloc(size + 1, sizeof(char));
	if (!nstr)
		return (NULL);
	copy_to_str(str, &nstr, env);
	return (nstr);
}
