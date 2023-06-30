/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:04:03 by orazafy           #+#    #+#             */
/*   Updated: 2023/06/30 14:06:26 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_function(int signum, siginfo_t *siginfo, void *ptr)
{
	(void)ptr;
	if (signum == SIGINT)
	{
		if (siginfo->si_pid == 0)
		{
			write(1, "\n", 1);
			g_minishell.exit_status = 130;
		}
		else
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_minishell.exit_status = 1;
		}
	}
}

void	ft_init_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler_function;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa, 0) == -1)
		exit(1);
	if (sigaction(SIGQUIT, &sa, 0) == -1)
		exit(1);
}
