/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_in_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:04:53 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/25 12:54:11 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	sigle_cote(t_token *curr, bool squote, bool dquote);
void	tenv_error_code(t_token *curr, int code);
void	tenv_varenv(t_token *curr, t_env *env, bool squote);
bool	double_cote(t_token *curr, bool dquote);

/* ************************************************************** */

void	get_val_tenv(int code, t_lexer *lexer, t_env *env)
{
	char	*value;
	bool	in_squote;
	bool	i_dquote;
	t_token	*curr;

	curr = lexer->header;
	value = NULL;
	(void)value;
	in_squote = false;
	i_dquote = false;
	while (curr != NULL)
	{
		if (curr->type == VAR_ENV && curr->value[1] != '?'
			&& ft_strlen(curr->value) >= 2)
			tenv_varenv(curr, env, in_squote);
		else if (curr->type == VAR_ENV && curr->value != NULL
			&& curr->value[1] == '?' && ft_strlen(curr->value) == 2)
			tenv_error_code(curr, code);
		i_dquote = double_cote(curr, i_dquote);
		in_squote = sigle_cote(curr, in_squote, i_dquote);
		curr = curr->next;
	}
}

bool	sigle_cote(t_token *curr, bool squote, bool dquote)
{
	if (curr->type == S_QUOTES && squote == false && dquote == false)
		return (true);
	if (curr->type == S_QUOTES && squote == true)
		return (false);
	return (squote);
}

bool	double_cote(t_token *curr, bool dquote)
{
	if (curr->type == D_QUOTES && dquote == false)
		return (true);
	if (curr->type == D_QUOTES && dquote == true)
		return (false);
	return (dquote);
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
	if (squote == false)
	{
		value = ft_strdup(ft_env_get_value(env, &curr->value[1]));
		if (value == NULL)
		{
			free(curr->value);
			curr->value = ft_strdup("");
			return ;
		}
		free(curr->value);
		curr->value = ft_strdup(value);
		free(value);
	}
}
