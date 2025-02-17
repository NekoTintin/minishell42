/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/17 16:34:44 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtin.h"

int main(int argc, char **argv, char **envp)
{
    if(argc == 1 )
        return (EXIT_FAILURE);
    /*mini_pwd();
    chdir(argv[1]);
     mini_pwd();*/
    mini_echo(argv);
    mini_exit();
    printf("after exit");
    return (EXIT_SUCCESS);
}