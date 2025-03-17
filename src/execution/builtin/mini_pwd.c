/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:36:49 by bchallat          #+#    #+#             */
/*   Updated: 2025/03/14 14:11:13 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	mini_pwd(void)
{
	//char	buffer[PATH_MAX];
	char	buffer[5000];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		ft_putstr_fd("pwd: error retrieving current directory", 2);
		perror("getcwd: cannot access parent directories");
		return (1);
	}
	ft_printf("%s\n", buffer);
	return (0);
}
