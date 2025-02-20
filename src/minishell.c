/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qupollet <qupollet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 16:07:42 by qupollet          #+#    #+#             */
/*   Updated: 2025/02/20 20:17:34 by qupollet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_parser(t_parser *parser)
{
	t_cmd	*cmd;
	int		i;

	cmd = parser->top;
	while (cmd != NULL)
	{
		printf("\nNouvelle Commande\n");
		i = -1;
		printf("Args:\n");
		if (cmd->args)
			while (cmd->args[++i])
				printf(" - %s\n", cmd->args[i]);
		i = -1;
		printf("infile:\n");
		if (cmd->infile)
			while (cmd->infile[++i])
				printf(" - %s\n", cmd->infile[i]);
		else
			printf(" - (null)\n");
		i = -1;
		printf("outfile:\n");
		if (cmd->outfile)
			while (cmd->outfile[++i])
				printf(" - %s\n", cmd->outfile[i]);
		else
			printf(" - (null)\n");
		i = -1;
		printf("append:\n");
		if (cmd->append)
			while (cmd->append[++i] != -1)
				printf(" - outfile %d is append: %d\n", i, cmd->append[i]);
		else
			printf(" - (null)\n");
		printf("delimiter:\n");
		if (cmd->delimiter)
		{
			printf(" - %s\n", cmd->delimiter);
			printf(" - Delete tabs ? %d\n", cmd->delete_tabs);
		}
		else
			printf(" - (null)\n");
		cmd = cmd->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_lexer		*lexer;
	char		*str;
	t_parser	*parser;

	(void)argc;
	(void)argv;
	str = readline("test > ");
	lexer = mi_make_lexer(str);
	if (!lexer)
		return (-1);
	parser = parsing(lexer, envp);
	if (!parser)
		return (-1);
	ll_free_lexer(lexer);
	free(str);
	ft_print_parser(parser);
	ft_free_parser(parser);
	printf("\n\n\n\n\n\n");
}
