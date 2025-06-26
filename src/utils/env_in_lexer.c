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
char	*tenv_error_code(char *str, int code, int index);
void	tenv_varenv(t_token *curr, t_env *env, bool squote);
bool	double_cote(t_token *curr, bool dquote);
char	*ft_strndup(char *str, unsigned int n);

/* ************************************************************** *

void	get_val_tenv(int code, t_lexer *lexer, t_env *env)
{
	char	*value;
	bool	in_squote;
	bool	i_dquote;
	t_token	*curr;

	curr = lexer->header;
	value = NULL;
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
* ******************************************************************* */
void	get_val_tenv(int code, t_lexer *lexer, t_env *env)
{
	bool	in_squote;
	bool	i_dquote;
	t_token	*curr;
	int 	index;

	curr = lexer->header;
	in_squote = false;
	i_dquote = false;
	while (curr != NULL)
	{
		index = 0;
		while (curr->value[index] != '\0')
		{
		/*	if (curr->value[index] == 36 && curr->value[index + 1] != '?')
				curr->value = tenv_varenv(curr, env, in_squote);*/
			if (curr->type == VAR_ENV && curr->value[1] != '?'
			&& ft_strlen(curr->value) >= 2)
				tenv_varenv(curr, env, in_squote);
			if (curr->value[index] == 36 && curr->value[index + 1] == 63)
				curr->value = tenv_error_code(curr->value, code, index);
			index++;
		}	
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

char	*tenv_error_code(char *str, int code, int index)
{
	char	*value;
	char	*befor;
	char	*after;
	char	*join;
	char	*join2;

	value = ft_itoa(code);
	befor = ft_strndup(str, index);
	after = ft_strndup(&str[index + 2], ft_strlen(str) - (index + 2));
	join = ft_strjoin(befor, value);
	join2 = ft_strjoin(join, after);
	free(value);
	free(befor);
	free(after);
	free(join);
	free(str);
	index = 0;
	return(join2);
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

char	*ft_strndup(char *str, unsigned int n)
{
	char	*dup;
	unsigned int	d;

	d = 0;
	dup = (char *)malloc(sizeof(char) * n + 1);
	if (str == NULL || dup == NULL)
		return (NULL);
	while(d != n)
	{
		dup[d] = str[d];
		d++;
	}
	dup[d] = 0x0;
	return (dup);
}
