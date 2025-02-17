/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:36:17 by bchallat          #+#    #+#             */
/*   Updated: 2025/02/17 14:47:12 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

int    mini_env(char **envp);

int     mini_env(char **envp)
{
    int     index;

    index = 0;
    if (envp == NULL)
        return (-1);
    while (envp[index] != NULL)
    {
        printf("%s\n", envp[index]);
        index++;
    }
    return (0);
}