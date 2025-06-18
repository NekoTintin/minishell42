/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:30:17 by unbuntu           #+#    #+#             */
/*   Updated: 2025/06/18 19:25:31 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/exec.h"

int	cd_tab_size(char **args)
{
	int		size;
	int		idx;

	size = 0;
	idx = 0;
	while (args[idx])
	{
		size++;
		idx++;
	}
	return (size);
}

int	cd_update_env(t_env *env, char *oldpwd, char **pwd)
{
	if (ft_add_to_env(env, "OLDPWD", oldpwd) == -1)
		return (free(*pwd), 1);
	if (ft_add_to_env(env, "PWD", *pwd) == -1)
		return (free(*pwd), 1);
	free(*pwd);
	return (0);
}

char	*set_dir(char **tb, int size)
{
	if (size == 1)
		return (ft_strdup("."));
	return (ft_strdup(tb[1]));
}

int	mini_cd(char **args, t_env *env)
{
	char		*dir;
	int			size;
	char		oldpwd[PATH_MAX];
	char		**tb;

	tb = rm_whitespace_tab(args);
	if (!tb)
		return (perror("malloc"), 1);
	size = cd_tab_size(tb);
	if (size > 2)
		return (free_tab(tb),
			ft_putstr_fd("bash: cd: too many arguments\n", 2), 1);
	dir = set_dir(tb, size);
	free_tab(tb);
	if (!dir)
		return (perror("malloc"), 1);
	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory", 2);
		perror("getcwd: cannot access parent directories");
		return (free(dir), 1);
	}
	if (chdir(dir) == -1)
		return (ft_putstr_fd("bash: cd: ", 2), perror(dir), free(dir), 1);
	return (cd_update_env(env, oldpwd, &dir));
}
