/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/18 18:11:11 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/builtin.h"

static void test_call_builtin(t_cmd *cmd);

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

static void test_call_builtin(t_cmd *cmd)
{
    if (!ft_strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])))
        mini_cd(cmd->args[1]);
    else if (!ft_strncmp(cmd->args[0], "exit", ft_strlen(cmd->args[0])))
        mini_exit();
    else if (!ft_strncmp(cmd->args[0], "export", ft_strlen(cmd->args[0])))
        printf("export\n");
    else if (!ft_strncmp(cmd->args[0], "unset", ft_strlen(cmd->args[0])))
        printf("unset\n");
    else if (!ft_strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])))
        mini_emvp(cmd->args[0]);
}