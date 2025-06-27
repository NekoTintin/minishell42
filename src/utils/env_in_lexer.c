/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_in_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 12:04:53 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/26 14:04:48 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_val_tenv(int code, t_lexer *lexer, t_env *env)
{
	bool	in_squote;
	bool	i_dquote;
	t_token	*curr;

	curr = lexer->header;
	in_squote = false;
	i_dquote = false;
	while (curr != NULL)
	{
		curr = loop_expand(curr, in_squote, code, env);
		i_dquote = double_cote(curr, i_dquote);
		in_squote = sigle_cote(curr, in_squote, i_dquote);
		curr = curr->next;
	}
}

t_token	*loop_expand(t_token *curr, bool in_squote, int code, t_env *env)
{
	int	index;

	index = 0;
	while (curr->value[index] != '\0')
	{
		if (curr->value[index] == 36 && \
			curr->value[index + 1] != '\0' && curr->value[index + 1] != '?')
			curr->value = tenv_varenv(curr->value, env, in_squote, index);
		if (curr->value == NULL || curr->value[0] == '\0' || \
			curr->value[index] == '\0')
			return (curr);
		else if (curr->value[index] == 36 && curr->value[index + 1] == 63)
			curr->value = tenv_error_code(curr->value, code, index);
		index++;
	}
	return (curr);
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
	return (join2);
}
