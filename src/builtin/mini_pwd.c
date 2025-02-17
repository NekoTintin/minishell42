/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:36:49 by bchallat          #+#    #+#             */
/*   Updated: 2025/02/17 13:57:32 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int    mini_pwd(void);

int    mini_pwd(void)
{
    char buffer[PATH_MAX];
    
    if (getcwd(buffer, sizeof(buffer)) == NULL)
        return (-1);
    else
        return (printf("%s\n", buffer));
    return (-1);
}