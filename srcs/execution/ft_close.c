/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:19:18 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/09 16:04:05 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int *fd)
{
	close(*fd);
	*fd = -2;
}

void	ft_close_all_fds(void)
{
	t_cmd		cmd;
	t_data_env	data_env;

	cmd = g_minishell.cmd;
	data_env = g_minishell.data_env;
	if (data_env.stdin != -2 && data_env.stdin != -1)
		ft_close(&data_env.stdin);
	if (data_env.stdout != -2 && data_env.stdout != -1)
		ft_close(&data_env.stdout);
	if (cmd.fd_in != -2 && cmd.fd_in != -1)
		ft_close(&cmd.fd_in);
	if (cmd.fd_out != -2 && cmd.fd_out != -1)
		ft_close(&cmd.fd_out);
	if (cmd.pipefd[0] != -2 && cmd.pipefd[0] != -1)
		ft_close(&cmd.pipefd[0]);
	if (cmd.old_pipefd[0] != -2 && cmd.old_pipefd[0] != -1)
		ft_close(&cmd.old_pipefd[0]);
	if (cmd.pipefd[1] != -2 && cmd.pipefd[1] != -1)
		ft_close(&cmd.pipefd[1]);
	if (cmd.old_pipefd[1] != -2 && cmd.old_pipefd[1] != -1)
		ft_close(&cmd.old_pipefd[1]);
	if (cmd.fd_heredoc != -2 && cmd.fd_heredoc != -1)
		ft_close(&cmd.fd_heredoc);
}
