/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/18 12:55:15 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "execution.h"
//#include "utils.h"
#include <linux/limits.h>

static t_parser  *test_make_fake_parser(void);

int main(int argc, char **argv)//, char **envp)
{   
    if (argc != 1 || argv[1] != NULL)
    {
        printf("NO argments accept in Minishell");
        exit(EXIT_FAILURE);
    }
    
    return (EXIT_SUCCESS);
}

static t_parser  *test_make_fake_parser(void)
{
    t_parser    *parser = (t_parser *)malloc(sizeof(parser));
    if (parser == NULL)
        return (NULL);
    
    
}