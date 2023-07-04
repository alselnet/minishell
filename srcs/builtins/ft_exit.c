/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 18:03:41 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/04 10:44:09 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned char	ft_atoi_exit(char *str)
{
	int	nb;
	int	i;

	if (*str == '+' || *str == '-')
		str++;
	i = 1;
	nb = str[0] % '0';
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] % '0');
		i++;
	}
	return (nb);
}

void	ft_exit_utils(int status, int no_exit_written)
{
	if (dup2(g_minishell.data_env.stdin, STDIN_FILENO) == -1)
		ft_error(1);
	if (dup2(g_minishell.data_env.stdout, STDOUT_FILENO) == -1)
		ft_error(1);
	if (no_exit_written == 0)
		write(1, "exit\n", 5);
	ft_close_all_fds();
	ft_free_cmd(&g_minishell.cmd);
	ft_free_env(g_minishell.data_env.envp, g_minishell.data_env.size);
	tk_clear(&g_minishell.ltable.tklist_head);
	free(g_minishell.ltable.input);
	rl_clear_history();
	exit(status);
}

void	ft_exit(int argc, char **argv)
{
	if (argc > 2)
	{
		ft_check_numeric_arg(argv, 0);
		write(2, "exit\n", 5);
		write(2, "exit: too many arguments\n", 25);
		g_minishell.exit_status = 1;
	}
	else if (argc == 1)
		ft_exit_utils(g_minishell.exit_status, 0);
	else
	{
		ft_check_numeric_arg(argv, 0);
		ft_exit_utils(ft_atoi_exit(argv[1]), 0);
	}
}
