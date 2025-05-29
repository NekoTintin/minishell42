/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:53:34 by bchallat          #+#    #+#             */
/*   Updated: 2025/05/29 14:45:33 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			mini_loop(t_minishell *mini);
t_minishell	*mini_init(void);
void		handle_sigint(int sig);

int	main(int argc, char **argv)
{
	t_minishell	*mini;

	mini = mini_init();
	signal(SIGINT, handle_sigint);
	if (argc == 1 && argv[1] == NULL)
		mini_loop(mini);
	free(mini);
	return (EXIT_SUCCESS);
}

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\nMinishell$");
	fflush(stdout);
}

t_minishell	*mini_init(void)
{
	t_minishell	*mini;

	mini = (t_minishell *)malloc(sizeof(t_minishell));
	mini->lexer = NULL;
	mini->parse = NULL;
	mini->status = true;
	return (mini);
}

int	mini_loop(t_minishell *mini)
{
	char		*line;

	line = NULL;
	while (mini->status == true)
	{
		line = readline("Minishell$ ");
		add_history(line);
		if (line == NULL)
			return (free(line), rl_clear_history(), EXIT_SUCCESS);
		else if (line[0] == '\0')
			free(line);
		else
		{
			mini->lexer = mi_make_lexer(line);
			mini->parse = mi_make_parse(mini->parse, mini->lexer);
			free_all_parser(mini->parse);
			line = NULL;
			mini->parse = NULL;
		}
	}
	rl_clear_history();
	free_all_parser(mini->parse);
	free(line);
	return (EXIT_SUCCESS);
}

/*void	mini_free_all(t_minishell *mini)
{
	
}*/
