/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:02:10 by qupollet          #+#    #+#             */
/*   Updated: 2025/04/04 18:06:27 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var(char *name, int end, char **envp)
{
	char	*key;
	int		idx;
	int		size;

	if (!name || !name[0] || !envp || !envp[0])
		return (NULL);
	key = ft_substr(name, 0, end);
	if (!key)
		return (NULL);
	idx = 0;
	size = ft_strlen(key);
	while (envp[idx])
	{
		if (ft_strncmp(envp[idx], key, size) == 0
			&& envp[idx][size] == '=')
		{
			free(key);
			return (envp[idx] + size + 1);
		}
		idx++;
	}
	free(key);
	return (NULL);
}

int	var_get_size(char *str, char **envp)
{
	int		idx;
	int		size;
	int		end;

	idx = -1;
	size = 0;
	while (str[++idx])
	{
		if (str[idx] == '$' && str[idx + 1])
		{
			end = idx + 1;
			if (ft_isdigit(str[end]))
				size++;
			else if (ft_isalpha(str[end]) || str[end] == '_')
			{
				while (ft_isalpha(str[end]) || str[end] == '_')
					end++;
				size += ft_strlen(get_var(&str[idx], end, envp));
			}
			idx = end - 1;
		}
		else
			size++;
	}
	return (size);
}

char	*var_strcpy(char *src, char *dst, int start)
{
	int		idx;

	idx = 0;
	while (src[idx])
	{
		dst[start + idx] = src[idx];
		idx++;
	}
	return (dst);
}

int	var_strdup(char *src, char **dst, char **envp)
{
	int		idx;
	int		end;
	int		pos;
	char	*val;

	idx = -1;
	pos = 0;
	while (src[++idx])
	{
		if (src[idx] == '$' && src[idx + 1])
		{
			end = idx + 1;
			if (ft_isalpha(src[end]) || src[end] == '_')
			{
				while (ft_isalpha(src[end]) || src[end] == '_')
					end++;
				val = get_var(&src[idx], end, envp);
				if (val)
				{
					var_strcpy(val, dst, pos);
					pos += ft_strlen(val);
				}
				idx = end - 1;
			}
		}
		else
			dst[pos++] = src[idx];
	}
	dst[pos] = '\0';
	return (pos);
}

int	exec_replace_env_var(char **str, char **envp)
{
	int			size;
	char		*fstr;

	if (!str || !str[0] || !envp || !envp[0])
		return (-1);
	size = var_get_size(&str, envp);
	if (size < 0)
		return (1);
	fstr = ft_calloc(size, sizeof(char));
	if (!fstr)
		return (1);
	if (var_strdup(&str, fstr, envp) == 1)
	{
		free(fstr);
		return (NULL);
	}
	return (fstr);
}
