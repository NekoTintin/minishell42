/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:21:26 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/25 13:35:00 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_minishell	*mini_init(char **envp)
{
	t_minishell	*mini;

	mini = (t_minishell *)malloc(sizeof(t_minishell));
	mini->line = NULL;
	mini->lexer = NULL;
	mini->parse = NULL;
	mini->env = ft_create_tenv(envp);
	if (mini->env == NULL)
		return (NULL);
	mini->status = true;
	return (mini);
}

void	mini_free(t_minishell *mini)
{
	if (mini->parse != NULL)
		free_all_parser(mini->parse);
	if (mini->env != NULL)
		ft_free_env(mini->env);
	if (mini->line != NULL)
		free(mini->line);
	rl_clear_history();
	free (mini);
}

int	mini_exec_line(t_minishell *mini, int *code_error)
{
	mini->lexer = mi_make_lexer(mini->line);
	if (mini->lexer == NULL)
		return (EXIT_FAILURE);
	free(mini->line);
	get_val_tenv(*code_error, mini->lexer, mini->env);
	mini->parse = mi_make_parse(mini->parse, mini->lexer);
	if (mini->parse == NULL)
		*code_error = 2;
	else if (mini->parse != NULL)
	{
		*code_error = exec_main(mini->parse, mini->env, mini);
		if (*code_error == -1)
			return (EXIT_FAILURE);
	}
	else
		*code_error = 1;
	mini->line = NULL;
	free_all_parser(mini->parse);
	mini->parse = NULL;
	return (EXIT_SUCCESS);
}
