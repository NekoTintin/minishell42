/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:53:34 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/11 20:17:00 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			mini_loop(t_minishell *mini);
t_minishell	*mini_init(void);
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		mini_free(t_minishell *mini);

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;

	mini = mini_init();
	mini->env = ft_create_tenv(envp);
	if (mini->env == NULL)
		return (EXIT_FAILURE);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (argc == 1 && argv[1] == NULL)
		mini_loop(mini);
	mini_free(mini);
	free(mini); // free all struct
	return (EXIT_SUCCESS);
}

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\nMinishell$");
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

t_minishell	*mini_init(void)
{
	t_minishell	*mini;

	mini = (t_minishell *)malloc(sizeof(t_minishell));
	mini->lexer = NULL;
	mini->parse = NULL;
	//mini->env = ft_create_tenv(envp);
	mini->env = NULL;
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
			if (exec_main(mini->parse, mini->env) == -1)
				return (EXIT_FAILURE);
			free_all_parser(mini->parse);
			line = NULL;
			mini->parse = NULL;
		}
	}
	rl_clear_history();
	free(line);
	return (EXIT_SUCCESS);
}

void	mini_free(t_minishell *mini)
{
	if (mini->parse != NULL)
		free_all_parser(mini->parse);
	if (mini->env != NULL)
		ft_free_env(mini->env);
}
