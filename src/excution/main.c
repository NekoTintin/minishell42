/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:16:32 by unbuntu           #+#    #+#             */
/*   Updated: 2025/02/18 15:07:36 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "execution.h"

static t_parser  *test_make_fake_parser(void);
static t_parser  test_value_fake_parser(t_parser *parser);

int main(void)
{   
    t_parser *parser = test_make_fake_parser();

    printf("test is builtin %d | %s\n", parser->top->is_builtin, parser->top->args[0]);
    return (mi_execution(parser));
}

static t_parser  *test_make_fake_parser(void)
{
    t_parser    *parser = (t_parser *)malloc(sizeof(t_parser));
    t_cmd       *cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (parser == NULL || cmd == NULL)
        return (NULL);
    parser->top = cmd;
    test_value_fake_parser(parser);
    return (parser);
}

static t_parser  test_value_fake_parser(t_parser *parser)
{
    parser->top->is_builtin = 1;
    parser->top->args = (char **)malloc(1);
    parser->top->args[0] = ft_strdup("exit");
    //return (parser);
}