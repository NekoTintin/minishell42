/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:48:08 by bchallat          #+#    #+#             */
/*   Updated: 2025/06/23 17:34:02 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_sig = 0;

void	signal_handler(int signum)
{
	(void)signum;
	g_sig = SIGINT;
	rl_done = 1;
	rl_replace_line("", 0);
}

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	sig_setup_mini(void)
{
	g_sig = 0;
	rl_event_hook = event;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_setup_defaut(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
