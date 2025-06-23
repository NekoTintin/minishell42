/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:53:34 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/23 15:36:36 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			mini_loop(t_minishell *mini);

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;

	if (argc != 1 || argv[1] != NULL || envp == NULL)
		return (EXIT_FAILURE);
	mini = mini_init(envp);
	if (mini == NULL)
		return (EXIT_FAILURE);
	sig_setup_mini();
	mini_loop(mini);
	mini_free(mini);
	return (EXIT_SUCCESS);
}

int	mini_loop(t_minishell *mini)
{
	int		code_error;

	code_error = 0;
	while (mini->status == true)
	{
		mini->line = readline("Minishell$ ");
		add_history(mini->line);
		if (mini->line == NULL)
			return (free(mini->line), rl_clear_history(), EXIT_SUCCESS);
		else if (mini->line[0] == '\0')
			free(mini->line);
		else
		{
			if (mini_exec_line(mini, &code_error) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
	}
	rl_clear_history();
	free(mini->line);
	return (EXIT_SUCCESS);
}
