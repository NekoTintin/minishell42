/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:32:08 by bchallat          #+#    #+#             */
/*   Updated: 2025/02/26 12:52:43 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_parser    *pars_make_ast(t_parser *ast)
{
    ast = (t_parser *)malloc(sizeof(t_parser));
    if (ast == NULL)
        return (NULL);
    ast->top = NULL;
    ast->size = 0;
    return (ast);
}

t_cmd       *pars_make_cmd(t_cmd *cmd)
{
    cmd = (t_cmd *)malloc(sizeof(cmd));
    if (cmd == NULL)
        return (NULL);
    cmd->args = NULL;
    cmd->infile = NULL;
    cmd->outfile = NULL;
    cmd->delimiter = NULL;
    cmd->delete_tabs = -1;
    cmd->append = NULL;
    cmd->is_builtin =-1;
    cmd->next = NULL;
    return (cmd);
}

void    pars_free_ast(t_parser *ast)
{
    t_cmd   *curr;
    t_cmd   *c_free;

    curr = ast->top;
    while (curr != NULL)
    {
        c_free = curr;
        curr = curr->next;
        pars_free_cmd(c_free);
    }
    free(ast);
}

void    pars_free_cmd(t_cmd *cmd)
{
    pars_free_arr(cmd->args);
    pars_free_arr(cmd->infile);
    pars_free_arr(cmd->outfile);
    free(cmd->delimiter);
    free(cmd->append);
    free(cmd);
}

void    pars_free_arr(char **arr)
{
    int index;

    index = 0;
    while (arr[index] != NULL)
    {
        free(arr[index]);
        index++;
    }
    free(arr);
}