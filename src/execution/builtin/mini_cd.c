/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:30:17 by unbuntu           #+#    #+#             */
/*   Updated: 2025/06/27 13:50:28 by qupollet         ###   ########.fr       */
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
	char		absolute_pwd[PATH_MAX];

	free(*pwd);
	if (getcwd(absolute_pwd, sizeof(absolute_pwd)) == NULL)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		perror("getcwd: cannot access parent directories");
		return (1);
	}
	if (ft_add_to_env(env, "OLDPWD", oldpwd) == -1)
		return (1);
	if (ft_add_to_env(env, "PWD", absolute_pwd) == -1)
		return (1);
	return (0);
}

char	*set_dir(char **tb, int size)
{
	if (size == 1)
		return (ft_strdup("."));
	return (ft_strdup(tb[1]));
}

// Return to root si PWD not in env
int	mini_cd_return_to_slash(t_env *env)
{
	ft_putstr_fd("cd: error retrieving current directory: ", 2);
	perror("getcwd: cannot access parent directories");
	ft_putstr_fd("Minishell will now return to root\n", 2);
	if (chdir("/") == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		perror("/");
	}
	ft_add_to_env(env, "PWD", "/");
	return (1);
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
		free(dir);
		return (mini_cd_return_to_slash(env));
	}
	if (chdir(dir) == -1)
		return (ft_putstr_fd("bash: cd: ", 2), perror(dir), free(dir), 1);
	return (cd_update_env(env, oldpwd, &dir));
}
