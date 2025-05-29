/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:30:17 by unbuntu           #+#    #+#             */
/*   Updated: 2025/05/28 01:16:36 by qupollet         ###   ########.fr       */
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

int	cd_update_env(t_env *env, char *oldpwd, char *pwd)
{
	if (ft_add_to_env(env, "OLDPWD", oldpwd) == -1)
		return (1);
	if (ft_add_to_env(env, "PWD", pwd) == -1)
		return (1);
	return (0);
}

int	mini_cd(char **args, t_env *env)
{
	char		*dir;
	int			size;
	char		oldpwd[PATH_MAX];

	size = cd_tab_size(args);
	if (size > 2)
		return (ft_putstr_fd("bash: cd: too many arguments", 2), 1);
	if (size == 1)
		dir = ".";
	else
		dir = args[1];
	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory", 2);
		return (perror("getcwd: cannot access parent directories"), 1);
	}
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		perror(dir);
		return (1);
	}
	return (cd_update_env(env, oldpwd, dir));
}
