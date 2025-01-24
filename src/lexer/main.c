/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/24 10:05:33 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "lexer.h"
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
    t_lexer   *lexer;
    t_tokenization *curr;

    lexer = ft_init_lexer(lexer);
    if(lexer == NULL)
        printf("ERORR inti lexer \n");    
    printf("init ok size: %d \n", lexer->size);
    

    lexer = ft_add_token(lexer);
    if (lexer == NULL)
        printf("ERROR \n");
    printf("add token ok size: %d \n", lexer->size);
    curr = le_last_node(lexer);
    curr->value = ft_strdup("salut");



    lexer = ft_add_token(lexer);
    if (lexer == NULL)
        printf("ERROR \n");
    printf("add token ok size: %d \n", lexer->size);
    curr = lexer->header;
    curr->value = ft_strdup("ca va");

    printf("%s \n", lexer->header->value);
    printf("%s \n", lexer->header->next->value);
    ft_free_lexer(lexer);
}



/*  test pour le fichier lexer_utils.c */