/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:36:05 by bchallat          #+#    #+#             */
/*   Updated: 2025/02/17 15:18:20 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"

void    mini_echo(char **args);

void    mini_echo(char **args)
{
    int     index;

    if (args[1][0] == '-')
    {
        index = 2;
        printf("%s",args[index++]);
        while (args[index] != NULL)
            printf(" %s",args[index++]);
    }
    else if (args[1] != "-n")
    {
        index = 1;
        printf("%s",args[index++]);
        while (args[index] != NULL)
            printf(" %s",args[index++]);
        printf("\n");
    }
}