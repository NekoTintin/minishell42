/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:53:34 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/18 18:23:23 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			mini_loop(t_minishell *mini);
t_minishell	*mini_init(void);
void		handle_sigint(int sig);
void		handle_sigquit(int sig);
void		mini_free(t_minishell *mini);
void		mini_code_error(int code, t_lexer *lexer);

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\nMinishell$");
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

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
	int		code_error;

	line = NULL;
	code_error = 0;
	while (mini->status == true)
	{
		line = readline("Minishell$ ");
		add_history(line);
		if (line == NULL)
			return (free(line), clear_history(), EXIT_SUCCESS);
		else if (line[0] == '\0')
			free(line);
		else
		{
			mini->lexer = mi_make_lexer(line);
			free(line);
			mini->parse = mi_make_parse(mini->parse, mini->lexer);
			code_error = exec_main(mini->parse, mini->env);
			if (code_error == -1)
				return (EXIT_FAILURE);
			free_all_parser(mini->parse);
			line = NULL;
			mini->parse = NULL;
		}
	}
	clear_history();
	return (EXIT_SUCCESS);
}

void	mini_free(t_minishell *mini)
{
	if (mini->parse != NULL)
		free_all_parser(mini->parse);
	if (mini->env != NULL)
		ft_free_env(mini->env);
}

void	mini_code_error(int code, t_lexer *lexer)
{
	t_token	*curr;

	curr = lexer->header;
	while (curr != NULL)
	{
		if (curr->type == VAR_ENV && \
			curr->value[1] == '?' && ft_strlen(curr->value) == 2)
		{
			free(curr->value);
			curr->value = ft_itoa(code);
		}
		curr = curr->next;
	}
}
