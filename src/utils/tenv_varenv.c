/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tenv_varenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:39:16 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/26 15:39:24 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*return_join(char *value, char *befor, char *after)
{
	char	*join;
	char	*join2;

	join = ft_strjoin(befor, value);
	join2 = ft_strjoin(join, after);
	free(join);
	free(after);
	free(befor);
	free(value);
	return (join2);
}

char	*tenv_varenv(char *str, t_env *env, bool squote, int index)
{
	char	*value;
	char	*befor;
	char	*after;
	char	*key;

	key = env_strextra(str, index);
	value = ft_strdup(ft_env_get_value(env, &key[1]));
	if (squote == false && value == NULL)
	{
		index = 0;
		free(str);
		free(value);
		free(key);
		return (ft_strndup(str, index));
	}
	befor = ft_strndup(str, index);
	after = ft_strndup(&str[index + ft_strlen(key)], \
				ft_strlen(str) - (index + ft_strlen(key)));
	if (squote == false)
	{
		free(str);
		free(key);
		index = 0;
		return (return_join(value, befor, after));
	}
	return (str);
}

char	*ft_strndup(char *str, unsigned int n)
{
	char			*dup;
	unsigned int	d;

	d = 0;
	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (str == NULL || dup == NULL)
		return (NULL);
	while (d != n)
	{
		dup[d] = str[d];
		d++;
	}
	dup[d] = '\0';
	return (dup);
}

char	*env_strextra(char *str, unsigned int n)
{
	char			*key;
	unsigned int	len;
	int				i;

	len = n + 1;
	while (str[len] != '\0' && (ft_isalpha(str[len]) || str[len] == '_'))
		len++;
	key = (char *)malloc(sizeof(char) * (len - n) + 1);
	if (str == NULL || key == NULL)
		return (NULL);
	i = 0;
	while (len > i + n)
	{
		key[i] = str[i + n];
		i++;
	}
	key[i] = 0x0;
	return (key);
}
