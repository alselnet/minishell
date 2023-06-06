/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:04:03 by orazafy           #+#    #+#             */
/*   Updated: 2023/06/06 19:27:58 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include "minishell.h"

// void	handler_function(int signum, siginfo_t *siginfo, void *ptr)
// {
// 	(void)ptr;
// 	(void)siginfo;
// 	if (signum == SIGINT)
// 	{
// 		write(1, "\n", 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		g_minishell.exit_status = 1;
// 	}
// }

// void	ft_init_signals(void)
// {
// 	struct sigaction	sa;

// 	sa.sa_sigaction = handler_function;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = SA_SIGINFO;
// 	if (sigaction(SIGINT, &sa, 0) == -1)
// 		exit(1);
// 	if (sigaction(SIGQUIT, &sa, 0) == -1)
// 		exit(1);
// }