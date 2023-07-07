/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:34:54 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/07 20:56:52 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fork(t_cmd *cmd, t_data_env *data_env)
{
	if (cmd->pipe == 1 && cmd->fd_out == -2 && cmd->fd_out != -1)
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
		ft_exec_builtin(&g_minishell.cmd, data_env);
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
			ft_error(200);
		ft_close(&cmd->fd_in);
	}
	if (cmd->fd_out != -2 && cmd->fd_out != -1)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			ft_error(200);
	}
	if (cmd->pipe == 1 && cmd->fd_out == -2 && cmd->fd_out != -1)
	{
		ft_close(&cmd->pipefd[0]);
		if (dup2(cmd->pipefd[1], STDOUT_FILENO) == -1)
			ft_error(200);
		ft_close(&cmd->pipefd[1]);
	}
	if (cmd->fd_out != -2 && cmd->fd_out != -1)
		ft_close(&cmd->fd_out);
	if (cmd->fd_in == -1)
		ft_exit_exec(1);
	if (cmd->fd_out == -1)
		ft_exit_exec(1);
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

void	ft_exit_exec(int status)
{
	ft_close_all_fds();
	ft_free_cmd(&g_minishell.cmd);
	ft_free_env(g_minishell.data_env.envp, g_minishell.data_env.size);
	tk_clear(&g_minishell.ltable.tklist_head);
	free(g_minishell.ltable.input);
	rl_clear_history();
	exit(status);
}
