/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:36:49 by bchallat          #+#    #+#             */
/*   Updated: 2025/02/24 03:48:08 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	mini_pwd(void)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
		return (-1);
	ft_printf("%s\n", buffer);
	return (0);
}
