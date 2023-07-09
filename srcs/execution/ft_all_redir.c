/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 17:08:02 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/09 17:14:20 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_all_redir(t_cmd *cmd)
{
	if (cmd->old_pipefd[0] != -2
		&& cmd->old_pipefd[1] != -2 && cmd->fd_in == -2)
	{
		ft_close(&cmd->old_pipefd[1]);
		if (dup2(cmd->old_pipefd[0], STDIN_FILENO) == -1)
			ft_error(1);
		ft_close(&cmd->old_pipefd[0]);
	}
	ft_redir_files(cmd);
	if (cmd->pipe == 1 && cmd->fd_out == -2)
	{
		ft_close(&cmd->pipefd[0]);
		if (dup2(cmd->pipefd[1], STDOUT_FILENO) == -1)
			ft_error(200);
		ft_close(&cmd->pipefd[1]);
	}
	if (cmd->fd_out != -2 && cmd->fd_out != -1)
		ft_close(&cmd->fd_out);
	ft_error_redirections(cmd);
}

void	ft_redir_files(t_cmd *cmd)
{
	if (cmd->fd_in != -2 && cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			ft_error(200);
		ft_close(&cmd->fd_in);
	}
	if (cmd->fd_out != -2 && cmd->fd_out != -1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			ft_error(200);
	}
}

void	ft_error_redirections(t_cmd *cmd)
{
	if (cmd->fd_in == -1)
	{
		ft_error_no_such_file(cmd->error_infile);
		ft_exit_exec(1);
	}
	if (cmd->fd_out == -1)
		ft_exit_exec(1);
}
