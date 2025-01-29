/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unbuntu <unbuntu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:09:02 by unbuntu           #+#    #+#             */
/*   Updated: 2025/01/29 10:41:35 by unbuntu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "../../includes/minishell.h"
# include <signal.h>
# include <stddef.h>
# include <unistd.h>

//typedef struct s_singal t_signal;

typedef struct s_signal
{
	void		(*sig_handler_sigint)(int);
	sigset_t	sig_mask;
	int			sig_flag;
}	t_signal;

void	sig_handle_sigint(int sig);
void	sig_setup_signal(void);

#endif
