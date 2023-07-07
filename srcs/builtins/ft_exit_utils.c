/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 19:52:26 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/07 19:05:57 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_utils(int status, int no_exit_written)
{
	if (no_exit_written == 0
		&& ft_strcmp("exit", g_minishell.cmd.argv[0]) == 0
		&& g_minishell.cmd.inside_pipe != 1)
		write(1, "exit\n", 5);
	if (g_minishell.status_done == 0 && g_minishell.cmd.final_cmd == 1)
	{
		g_minishell.exit_status = status;
		g_minishell.status_done = 1;
	}
	if (g_minishell.cmd.inside_pipe == 1)
	{
		ft_close_all_fds();
		ft_free_cmd(&g_minishell.cmd);
		ft_free_env(g_minishell.data_env.envp, g_minishell.data_env.size);
		tk_clear(&g_minishell.ltable.tklist_head);
		free(g_minishell.ltable.input);
		rl_clear_history();
		exit(status);
	}	
}

int	ft_check_all_digits(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str) == 0)
			return (-1);
		str++;
	}
	return (0);
}

void	ft_error_numeric(char *builtin, char *identifier)
{
	write(2, builtin, ft_strlen(builtin));
	write(2, ": ", 2);
	write(2, identifier, ft_strlen(identifier));
	write(2, ": numeric argument required\n", 28);
}

int	ft_check_numeric_arg(char **argv)
{
	if (ft_check_all_digits(argv[1]) == -1)
	{
		if (g_minishell.cmd.inside_pipe != 1)
			write(2, "exit\n", 5);
		ft_error_numeric("exit", argv[1]);
		ft_exit_utils(2, 1);
		return (-1);
	}
	return (0);
}
