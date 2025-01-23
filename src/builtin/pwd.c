/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:47:36 by qupollet          #+#    #+#             */
/*   Updated: 2025/01/23 13:29:22 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <linux/limits.h>

char	*ft_pwd(void)
{
	char		buffer[PATH_MAX];
	char		*pwd;

	if (getcwd(buffer, sizeof(buffer)) == NULL)
		return (NULL);
	pwd = ft_strdup(buffer);
	if (pwd == NULL)
		return (NULL);
	return (pwd);
}
