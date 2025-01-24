/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/24 00:13:28 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
//#include "lexer.h"
#include <linux/limits.h>

/*int main(int argc, char **argv)//, char **envp)
{
    t_tools     tools;
    char        *path;
    char		buffer[PATH_MAX];
    
    if (argc != 1 || argv[1] != NULL)
    {
        printf("NO argments accept in Minishell");
        exit(EXIT_FAILURE);
    }
    getcwd(buffer, sizeof(buffer));
    path = ft_strdup(buffer);
    tools.prompt = ft_strjoin(path, " \033[1;33mminishell>\033[0m ");
    mini_loop(&tools);
    return (EXIT_SUCCESS);
}*/

int     main(int argc, char **argv)
{
    char    **split;

    if (argc == 1)
        return(EXIT_FAILURE);
    split = ft_split(argv[1], ' ');
    for(int i = 0; split[i] != NULL; i++)
        printf("%s\n", split[i]);
    return(EXIT_SUCCESS);
}



/*  test pour le fichier lexer_utils.c */