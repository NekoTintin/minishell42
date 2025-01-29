/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:08:54 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/29 10:53:13 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.h"

void	sig_handle_sigint(int sig);
void	sig_setup_signal(void);

void	sig_handle_sigint(int sig)
{
	(void) sig;
	ft_printf("Minishell$");
}

void	sig_setup_signal(void)
{
	t_signal	sig;

	sig.sig_handler_sigint = sig_handle_sigint;
	sig.sig_flag = SA_RESTART;
	sigemptyset(&sig.sig_mask);
	sigaction(SIGINT, &sig, NULL);
	signal(SIGQUIT, SIG_IGN);
}
