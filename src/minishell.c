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
t_minishell		*mini_init(void);
void			mini_free(t_minishell *mini);
void			mini_code_error(int code, t_lexer *lexer, t_env *env);



int	main(int argc, char **argv, char **envp)
{
	t_minishell	*mini;

	if (argc != 1 || argv[1] != NULL || envp == NULL)
		return (EXIT_FAILURE);	
	if ((mini = mini_init()) == NULL);
		return (EXIT_FAILURE);
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
			if ((mini->lexer = mi_make_lexer(mini->line)) == NULL)
				return (EXIT_FAILURE);
			free(mini->line);
			mini->line = NULL;
			mini_code_error(code_error, mini->lexer, mini->env);
			if ((mini->parse = mi_make_parse(mini->parse, mini->lexer) == NULL)
				return (EXIT_FAILURE);
			if ((code_error = exec_main(mini->parse, mini->env)) == -1);
				return (EXIT_FAILURE);
			free_all_parser(mini->parse);
			mini->parse = NULL;
		}
	}
	rl_clear_history();
	free(mini->line);
	return (EXIT_SUCCESS);
}

t_minishell	*mini_init(void)
{
	t_minishell	*mini;

	mini = (t_minishell *)malloc(sizeof(t_minishell));
	mini->line = NULL;
	mini->lexer = NULL;
	mini->parse = NULL;
	mini->env = ft_create_tenv(envp);
	if (mini->env == NULL)
		return (EXIT_FAILURE);
	mini->status = true;
	return (mini);
}

void	mini_free(t_minishell *mini)
{
	if (mini->parse != NULL)
		free_all_parser(mini->parse);
	if (mini->env != NULL)
		ft_free_env(mini->env);
	free(mini); 
}


/* ************************************************************** */

void	mini_code_error(int code, t_lexer *lexer, t_env *env)
{
	t_token	*curr;
	char	*value;

	curr = lexer->header;
	value = NULL;
	while (curr != NULL)
	{
		if (curr->type == VAR_ENV && \
			curr->value[1] == '?' && ft_strlen(curr->value) == 2)
		{
			free(curr->value);
			curr->value = ft_itoa(code);
		}
		if (curr->type == VAR_ENV && \
			curr->value[1] != '?' && ft_strlen(curr->value) > 2)
		{
			value = strdup(ft_env_get_value(env, &curr->value[1]));
			if (value == NULL)
				return ;
			free(curr->value);
			curr->value = ft_strdup(value);
			free(value);
		}
		curr = curr->next;
	}
}
