#include "minishell.h"

void    handle_sigint(int sig)
{
    printf("\n");
	if (g_signals.in_hdoc)
		ft_putstr_fd("\n", STDERR_FILENO);
	if (g_signals.in_cmd)
	{
		g_signals.stop_hdoc = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}


void    handle_sigquit(int sig)
{
    ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}


void start_signals(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}