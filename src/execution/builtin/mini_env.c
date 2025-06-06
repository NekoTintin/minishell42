/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:36:17 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/06 13:25:31 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

int	mini_env(t_env *env)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (cur->key || cur->value)
			printf("%s=%s\n", cur->key, cur->value);
		else if (cur->key)
			printf("%s=\n", cur->key);
		cur = cur->next;
	}
	return (0);
}
