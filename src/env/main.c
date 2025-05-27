/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:09:36 by qupollet          #+#    #+#             */
/*   Updated: 2025/05/27 21:29:46 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_tenv(t_env *env)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
}

void	print_tab(char **tablo)
{
	int	i;

	i = 0;
	while (tablo[i])
	{
		printf("%s\n", tablo[i]);
		i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	**tablo;

	(void)argc;
	(void)argv;
	env = ft_create_tenv(envp);
	tablo = ft_env_to_tab(env);
	if (!tablo)
	{
		printf("Tablo NULL\n");
		ft_free_env(env);
		return (1);
	}
	print_tab(tablo);
	ft_free_env(env);
	free_tab(tablo);
	return (0);
}
