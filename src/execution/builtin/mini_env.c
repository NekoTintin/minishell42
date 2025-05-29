/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:36:17 by bchallat          #+#    #+#             */
/*   Updated: 2025/05/28 01:02:37 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

int	mini_env(t_env *env)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (!cur->key || !cur->value)
			return (1);
		printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
	return (0);
}
