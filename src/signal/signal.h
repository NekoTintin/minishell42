#ifdef SIGNAL_H
#	define SIGNAL_H
#inlcude "../../includes/minishell"

void	sig_handle_sigint(int sig);
void	sig_setup_signal(void);

#endif
