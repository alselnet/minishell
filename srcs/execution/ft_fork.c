/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:34:54 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/09 17:11:35 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fork(t_cmd *cmd, t_data_env *data_env)
{
	cmd->pid = fork();
	if (cmd->final_cmd)
		cmd->final_pid = cmd->pid;
	if (cmd->pid < 0)
		ft_error(1);
	else if (cmd->pid == 0)
	{
		ft_all_redir(cmd);
		if (cmd->has_cmd == 0 && cmd->first_arg != NULL)
			ft_error_cmd_not_found(cmd->first_arg);
		if (cmd->has_cmd == 0 && cmd->first_arg == NULL)
			ft_exit_exec(0);
		ft_close_all_fds();
		ft_exe_builtin2(&g_minishell.cmd, data_env);
		ft_exec_not_builtin(cmd, data_env);
	}
	else
		ft_after_fork_parent(cmd);
}

void	ft_exec_not_builtin(t_cmd *cmd, t_data_env *data_env)
{
	struct stat	f_stat;

	if (!access(cmd->argv[0], X_OK))
		cmd->cmd_path = ft_strdup(cmd->argv[0]);
	else
		cmd->cmd_path = find_cmd_path(cmd->argv[0], data_env->envp);
	if (cmd->cmd_path == NULL)
		ft_error(200);
	close(data_env->stdin);
	close(data_env->stdout);
	if (stat(cmd->cmd_path, &f_stat) == -1)
	{
		perror("");
		ft_exit_exec(1);
	}
	if (S_ISDIR(f_stat.st_mode))
	{
		write(2, cmd->cmd_path, ft_strlen(cmd->cmd_path));
		write(2, ": Is a directory\n", 17);
		ft_exit_exec(126);
	}
	execve(cmd->cmd_path, cmd->argv, data_env->envp);
	ft_error(200);
}

void	ft_after_fork_parent(t_cmd *cmd)
{
	if (cmd->old_pipefd[0] != -2 && cmd->old_pipefd[1] != -2)
	{
		ft_close(&cmd->old_pipefd[0]);
		ft_close(&cmd->old_pipefd[1]);
	}
	cmd->old_pipefd[0] = cmd->pipefd[0];
	cmd->old_pipefd[1] = cmd->pipefd[1];
	if (cmd->fd_in != -2 && cmd->fd_in != -1)
		ft_close(&cmd->fd_in);
	if (cmd->fd_out != -2 && cmd->fd_out != -1)
		ft_close(&cmd->fd_out);
}

void	ft_exe_builtin2(t_cmd *cmd, t_data_env *data_env)
{
	if (cmd->argv != NULL)
	{
		if (ft_strcmp("echo", cmd->argv[0]) == 0)
			ft_echo(cmd->argc, cmd->argv);
		else if (ft_strcmp("cd", cmd->argv[0]) == 0)
			ft_cd(cmd->argc, cmd->argv, data_env);
		else if (ft_strcmp("pwd", cmd->argv[0]) == 0)
			ft_pwd(data_env->envp);
		else if (ft_strcmp("export", cmd->argv[0]) == 0)
			ft_export(cmd->argc, cmd->argv, data_env);
		else if (ft_strcmp("unset", cmd->argv[0]) == 0)
			ft_unset(cmd->argc, cmd->argv, data_env);
		else if (ft_strcmp("env", cmd->argv[0]) == 0)
			ft_env(data_env-> envp, cmd->argc);
		else if (ft_strcmp("exit", cmd->argv[0]) == 0)
			ft_exit(cmd->argc, cmd->argv);
	}
}
