/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/22 14:08:34 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "testeur.h"

void handle_sigint(int sig) {
    (void)sig;
    printf("\nMinishell$ ");
    fflush(stdout);
}

int     main(int argc, char **argv)//, char **envp)
{
    signal(SIGINT, handle_sigint);
    
    if (argc != 1 && argv != NULL)
        return (EXIT_FAILURE);

    char        *string = NULL;
    t_lexer     *lexer = NULL;

    while (string == NULL)
    {
        string = readline("Minishell$ ");
        if (string == NULL)
            return (free(string), EXIT_SUCCESS);
        else if (*string == '\0')
            free(string);
        else
        {
            lexer = test_mi_lexer(string, lexer);
            if (lexer == NULL)
                return (free(lexer),EXIT_FAILURE);
        }
        string = NULL;
    }
    return (free(string), EXIT_SUCCESS);
}