/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_in_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:04:53 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/24 17:10:21 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	sigle_cote(t_token *curr, bool squote);
void	tenv_error_code(t_token *curr, int code);
void	tenv_varenv(t_token *curr, t_env *env, bool squote);

/* ************************************************************** */

void	get_val_tenv(int code, t_lexer *lexer, t_env *env)
{
	char	*value;
	bool	in_squote;
	t_token	*curr;

	curr = lexer->header;
	value = NULL;
	(void)value;
	in_squote = false;
	while (curr != NULL)
	{

		if (curr->type == VAR_ENV && \
			curr->value[1] != '?' && ft_strlen(curr->value) > 2)
			tenv_varenv(curr, env, in_squote);
		if (curr->type == VAR_ENV && \
			curr->value[1] == '?' && ft_strlen(curr->value) == 2)
			tenv_error_code(curr, code);
		in_squote = sigle_cote(curr, in_squote);
		curr = curr->next;
	}
}

bool	sigle_cote(t_token *curr, bool squote)
{
	if (curr->type == S_QUOTES && squote == false)
		return (true);
	if (curr->type == S_QUOTES && squote == true)
		return (false);
	return (squote);
}

void	tenv_error_code(t_token *curr, int code)
{
	char	*value;

	value = NULL;
	value = ft_itoa(code);
	free(curr->value);
	curr->value = ft_strdup(value);
	free(value);
}

void	tenv_varenv(t_token *curr, t_env *env, bool squote)
{
	char	*value;

	value = NULL;
	if (squote == true)
	{
		value = ft_strdup(&curr->value[1]);
		if (value == NULL)
			return ;
		free(curr->value);
		curr->value = ft_strdup(value);
		free(value);
	}
	else
	{
		value = ft_strdup(ft_env_get_value(env, &curr->value[1]));
		if (value == NULL)
		{
			curr->value = NULL;
			return ;
		}
		free(curr->value);
		curr->value = ft_strdup(value);
		free(value);
	}
}
