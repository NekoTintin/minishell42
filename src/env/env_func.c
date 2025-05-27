/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 22:01:23 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/27 22:54:53 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_add_to_env(t_env *top, char *key, char *val)
{
	t_env	*cur;
	t_env	*new_node;

	if (ft_env_get_value(top, key) != NULL)
		return (1);
	cur = top;
	while (cur->next)
		cur = cur->next;
	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (1);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
		return (free(new_node), 1);
	new_node->value = ft_strdup(val);
	if (!new_node->value)
		return (free(new_node->key), free(new_node), 1);
	cur->next = new_node;
	return (0);
}

char	*ft_env_get_value(t_env *env, char *key)
{
	t_env		*cur;
	char		*value;

	cur = env;
	value = NULL;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(cur->key)) == 0
			&& cur->key[ft_strlen(cur->key)] == '\0')
			value = cur->value;
		cur = cur->next;
	}
	return (value);
}

char	**ft_env_to_tab(t_env *env)
{
	t_env	*cur;
	int		len;
	int		size;
	char	**new_tab;
	char	*tmp;

	size = exec_env_size(env);
	new_tab = ft_calloc(size + 1, sizeof(char *));
	if (!new_tab)
		return (NULL);
	cur = env;
	len = 0;
	while (cur && len < size)
	{
		tmp = ft_strjoin(cur->key, "=");
		if (!tmp)
			return (free_tab(new_tab), NULL);
		new_tab[len] = ft_strjoin(tmp, cur->value);
		free(tmp);
		if (!new_tab[len])
			return (free_tab(new_tab), NULL);
		cur = cur->next;
		len++;
	}
	return (new_tab);
}

int	env_remove(t_env **env, char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(cur->key)) == 0
			&& cur->key[ft_strlen(cur->key)] == '\0')
		{
			if (!prev)
				*env = cur->next;
			else
				prev->next = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return (0);
		}
		prev = cur;
		cur = cur->next;
	}
	return (1);
}
