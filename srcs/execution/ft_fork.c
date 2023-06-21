/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:34:54 by orazafy           #+#    #+#             */
/*   Updated: 2023/06/21 18:23:47 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fork(t_cmd *cmd, t_data_env *data_env)
{
	if (cmd->pipe == 1 && cmd->fd_out == -2)
	{
		if (pipe(cmd->pipefd) == -1)
			ft_error(1);
	}
	cmd->pid = fork();
	if (cmd->final_cmd)
		cmd->final_pid = cmd->pid;
	if (cmd->pid < 0)
		ft_error(1);
	else if (cmd->pid == 0)
	{
		ft_redirections(cmd);
		if (cmd->has_cmd == 0)
			ft_error_cmd_not_found(cmd->first_arg);
		ft_exe_builtin2(cmd, data_env);
		ft_exec_not_builtin(cmd, data_env);
	}
	else
		ft_after_fork_parent(cmd);
}

void	ft_redirections(t_cmd *cmd)
{
	if (cmd->fd_in != -2 && cmd->fd_in != -1)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			ft_error(2);
		ft_close(&cmd->fd_in);
	}
	if (cmd->fd_out != -2)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			ft_error(2);
	}
	if (cmd->pipe == 1 && cmd->fd_out == -2)
	{
		ft_close(&cmd->pipefd[0]);
		if (dup2(cmd->pipefd[1], STDOUT_FILENO) == -1)
			ft_error(2);
		ft_close(&cmd->pipefd[1]);
	}
	if (cmd->fd_out != -2)
		ft_close(&cmd->fd_out);
	if (cmd->fd_in == -1)
	{
		ft_close_all_fds();
		exit(1);
	}
}

void	ft_exe_builtin2(t_cmd *cmd, t_data_env *data_env)
{
	if (ft_strcmp("echo", cmd->argv[0]) == 0)
		ft_echo(cmd->argc, cmd->argv);
	else if (ft_strcmp("env", cmd->argv[0]) == 0)
		ft_env(data_env->envp);
	else if (ft_strcmp("pwd", cmd->argv[0]) == 0)
		ft_pwd();
	else if (ft_strcmp("export", cmd->argv[0]) == 0 && cmd->argc == 1)
		ft_export(cmd->argc, cmd->argv, data_env);
}

void	ft_exec_not_builtin(t_cmd *cmd, t_data_env *data_env)
{
	cmd->cmd_path = find_cmd_path(cmd->argv[0], data_env->envp);
	if (cmd->cmd_path == NULL)
		ft_error(2);
	close(data_env->stdin);
	close(data_env->stdout);
	execve(cmd->cmd_path, cmd->argv, data_env->envp);
	ft_error(2);
}

void	ft_after_fork_parent(t_cmd *cmd)
{
	if (cmd->pipe == 1 && cmd->fd_out == -2)
	{
		ft_close(&cmd->pipefd[1]);
		if (dup2(cmd->pipefd[0], STDIN_FILENO) == -1)
			ft_error(1);
		ft_close(&cmd->pipefd[0]);
	}
	if (cmd->fd_in != -2 && cmd->fd_in != -1)
		ft_close(&cmd->fd_in);
	if (cmd->fd_out != -2 && cmd->fd_out != -1)
		ft_close(&cmd->fd_out);
}
