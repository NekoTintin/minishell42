/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:07:42 by qupollet          #+#    #+#             */
/*   Updated: 2025/01/27 15:17:49 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	char	*joined;
	char	*result;

	if (argc != 1)
		return (ft_putendl_fd(ERR_ARG, 2), 1);
	(void) argv;
	(void) envp;
	path = ft_pwd();
	joined = ft_strjoin(path, " \033[1;33mminishell>\033[0m ");
	if (!joined)
		return (1);
	free(path);
	while (1)
	{
		result = readline(joined);
		add_history(result);
		if (ft_strncmp(result, "pwd", 3) == 0)
			printf("%s\n", ft_pwd());
		else if (ft_strncmp(result, "exit", 4) == 0)
			break ;
		else
			printf("%s : %s\n", result, "command not found");
	}
	rl_clear_history();
	free(joined);
	free(result);
}
