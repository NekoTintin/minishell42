/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:48:15 by qupollet          #+#    #+#             */
/*   Updated: 2025/06/27 12:42:22 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_code(int code)
{
	if (code == 130)
		write(2, "\n", 1);
	if (code == 131)
		write(2, "Quit(core dumped)\n", 18);
}

int	ft_check_find_in_path_path(t_env *env, char **file)
{
	if (ft_env_get_value(env, "PATH") == NULL)
	{
		ft_print_errors(*file, 127);
		return (127);
	}
	if (!file || !*file || !**file)
		return (1);
	return (0);
}
