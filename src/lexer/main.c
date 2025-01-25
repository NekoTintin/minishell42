/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/25 10:44:53 by unbuntu          ###   ########.fr       */
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
static void     print_chain(t_lexer *lexer);

int     main(int argc, char **argv)
{
    t_lexer     *lexer = ll_init_lexer(lexer);
    t_token     *p_node;

    lexer = ll_add_token(lexer);
    lexer = ll_add_token(lexer);

    print_chain(lexer);
    ll_free_lexer(lexer);
    return (EXIT_SUCCESS);
}

static void    print_chain(t_lexer *lexer)
{
    t_token *node = lexer->header;

    while (node != NULL)
    {
        printf("-> valeur node: %s \n", node->value);
        printf("-> type   node: %d \n", node->type);
        node = node->next;
    }
}

/*  test pour le fichier lexer_utils.c */