/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:34:36 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/23 19:11:55 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_allocate_env(t_env *top, char **envp)
{
	t_env	*cur;
	int		i;
	int		y;

	if (!top)
		return (1);
	y = 0;
	while (envp[y])
		y++;
	cur = top;
	i = 1;
	while (i < y)
	{
		cur->next = ft_calloc(1, sizeof(t_env));
		if (!cur->next)
			return (1);
		cur = cur->next;
		i++;
	}
	return (0);
}

int	ft_fill_env(t_env *node, char *envp)
{
	int		egal_pos;

	if (!node || !envp)
		return (1);
	egal_pos = 0;
	while (envp[egal_pos] != '=' && envp[egal_pos] != '\0')
		egal_pos++;
	node->key = ft_substr(envp, 0, egal_pos);
	if (!node->key)
		return (1);
	if (envp[egal_pos] == '\0')
	{
		node->value = ft_strdup("");
		if (!node->value)
			return (free(node->key), 1);
		return (0);
	}
	node->value = ft_substr(envp, egal_pos + 1, ft_strlen(envp) - egal_pos - 1);
	if (!node->value)
		return (free(node->key), 1);
	return (0);
}

void	ft_free_env(t_env *top)
{
	t_env	*tmp;

	if (!top)
		return ;
	while (top)
	{
		tmp = top;
		top = top->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

t_env	*ft_create_tenv(char **envp)
{
	t_env	*top;
	t_env	*cur;
	int		i;

	if (!envp || !*envp || !envp[0])
		return (NULL);
	top = ft_calloc(1, sizeof(t_env));
	if (!top)
		return (NULL);
	if (ft_allocate_env(top, envp) == 1)
		return (ft_free_env(top), NULL);
	cur = top;
	i = 0;
	while (envp[i])
	{
		if (ft_fill_env(cur, envp[i]))
			return (ft_free_env(top), NULL);
		i++;
		cur = cur->next;
	}
	return (top);
}
