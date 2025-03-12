/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:42:31 by qupollet          #+#    #+#             */
/*   Updated: 2025/03/12 00:14:56 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close_pipe(int *input, int *output)
{
	if (input)
	{
		if (input[0] != -1 && close(input[0]) == -1)
			perror("bash: close failed");
		if (input[1] != -1 && close(input[1]) == -1)
			perror("bash: close failed");
	}
	if (output)
	{
		if (output[0] != -1 && close(output[0]) == -1)
			perror("bash: close failed");
		if (output[1] != -1 && close(output[1]) == -1)
			perror("bash: close failed");
	}
}

int	ft_has_redirect(t_cmd *cmd, t_token_type type_search)
{
	t_redirect		*cur;

	cur = cmd->redirect;
	while (cur)
	{
		if (cur->type == type_search)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int	ft_exec_builtin(t_cmd *cmd, char **envp)
{
	int	builtin_type;

	(void)envp;
	builtin_type = ft_is_builtin(cmd->argument[0]);
	if (builtin_type == 2)
		return (mini_cd(cmd->argument));
	if (builtin_type == 3)
		return (mini_pwd());
	return (127);
}

int	ft_is_builtin(const char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0 && (ft_strlen(str) == 4))
		return (1);
	else if (ft_strncmp(str, "cd", 2) == 0 && (ft_strlen(str) == 2))
		return (2);
	else if (ft_strncmp(str, "pwd", 3) == 0 && (ft_strlen(str) == 3))
		return (3);
	else if (ft_strncmp(str, "export", 6) == 0 && (ft_strlen(str) == 6))
		return (4);
	else if (ft_strncmp(str, "unset", 5) == 0 && (ft_strlen(str) == 5))
		return (5);
	else if (ft_strncmp(str, "env", 3) == 0 && (ft_strlen(str) == 3))
		return (6);
	else if (ft_strncmp(str, "exit", 4) == 0 && (ft_strlen(str) == 4))
		return (7);
	return (-1);
}
