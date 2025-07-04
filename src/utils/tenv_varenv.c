/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tenv_varenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:39:16 by bchallat          #+#    #+#             */
/*   Updated: 2025/07/02 20:11:01 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_vavenv(char *key, char *value, char *befor, char *after)
{
	free(key);
	free(value);
	free(befor);
	free(after);
}

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
	befor = ft_strndup(str, index);
	after = ft_strndup(&str[index + ft_strlen(key)],
			ft_strlen(str) - (index + ft_strlen(key)));
	index = -1;
	if (squote == false)
	{
		if (value == NULL)
		{
			free_vavenv(key, value, after, str);
			return (befor);
		}
		free(key);
		free(str);
		index = 0;
		return (return_join(value, befor, after));
	}
	free_vavenv(key, value, befor, after);
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
	while (str[len] != '\0'
		&& (ft_isalpha(str[len]) || str[len] == '_' || ft_isdigit(str[len])))
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

/*char	*tenv_varenv(char *str, t_env *env, bool squote, int index)
{
	char	*value;
	char	*befor;
	char	*after;
	char 	*key;
	char	*join;
	char	*join2;
	key = env_strextra(str, index);
	value = ft_strdup(ft_env_get_value(env,&key[1]));
	printf("%s \n", value);
	befor = ft_strndup(str, index);
	printf("%s \n", befor);
	after = ft_strndup(&str[index + ft_strlen(key)],
			ft_strlen(str) - (index + ft_strlen(key)));
	if (squote == false)
	{
		if (value == NULL)
		{
			free(after);
			free(value);
			free(str);
			free(key);
			index = 0;
			return(befor);
		}
		join = ft_strjoin(befor, value);
		printf("%s \n", join);
		join2 = ft_strjoin(join, after);
		printf("%s \n", join2);
		free(join);
		free(after);
		free(befor);
		free(value);
		free(str);
		free(key);
		index = 0;
		return (join2);
	}
	printf("<%d> \n", index);
	index = 0;
	return(str);
}*/
