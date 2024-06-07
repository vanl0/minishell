/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilorenzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:21:07 by ilorenzo          #+#    #+#             */
/*   Updated: 2024/06/05 18:21:09 by ilorenzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	handle_sigint(int sig)
{
	if (g_signals.in_hdoc)
	{
		g_signals.stop_hdoc = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	printf("\n");
	if (g_signals.in_cmd)
	{
		g_signals.stop_hdoc = 1;
		ft_putstr_fd("\n", STDERR_FILENO);
		rl_replace_line("", 0);
		rl_done = 1;
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	handle_sigquit(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	rl_redisplay();
	return ;
}

void	start_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
