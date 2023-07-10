/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:36:20 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/10 17:27:01 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute(t_token *tklist_head, t_data_env *data_env)
{
	int		builtin_done;
	int		pipe_before;

	builtin_done = 0;
	pipe_before = 0;
	ft_std_backup(data_env);
	g_minishell.cmd.old_pipefd[0] = -2;
	g_minishell.cmd.old_pipefd[1] = -2;
	while (1)
	{
		ft_init_cmd(&g_minishell.cmd);
		fetch_heredoc(&g_minishell.cmd, tklist_head, data_env);
		tklist_head = ft_get_cmd(tklist_head, &g_minishell.cmd, pipe_before);
		ft_execute_cmd(&g_minishell.cmd, data_env, builtin_done);
		if (g_minishell.cmd.final_cmd == 1)
			break ;
		ft_prepare_before_next_cmd(&pipe_before, &builtin_done);
	}
	ft_waitpid(&g_minishell.cmd);
	ft_restore_before_next_prompt(data_env, &g_minishell.cmd);
}

void	ft_execute_cmd(t_cmd *cmd, t_data_env *data_env, int builtin_done)
{
	if (pipe(cmd->pipefd) == -1)
		ft_error(1);
	if (cmd->inside_pipe == 0)
			builtin_done = ft_exe_builtin1(cmd, data_env);
	if (builtin_done == 0)
		ft_fork(cmd, data_env);
}

void	ft_prepare_before_next_cmd(int *pipe_before, int *builtin_done)
{
	*pipe_before = ft_init_pipe_before(&g_minishell.cmd);
	ft_free_cmd(&g_minishell.cmd);
	*builtin_done = 0;
}

void	ft_waitpid(t_cmd *cmd)
{
	int	res;
	int	status;

	res = 0;
	status = 0;
	while (res != -1 || errno != ECHILD)
	{
		res = waitpid(-1, &status, 0);
		if (res == cmd->final_pid)
		{
			if (WIFEXITED(status))
				g_minishell.exit_status = WEXITSTATUS(status);
			g_minishell.status_done = 1;
		}
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 200)
				ft_error(200);
		}
		if (res == -1 && (errno != EINTR && errno != ECHILD))
			ft_error(1);
	}
}

int	ft_exe_builtin1(t_cmd *cmd, t_data_env *data_env)
{
	if (cmd->argv != NULL)
	{
		if (ft_strcmp("cd", cmd->argv[0]) == 0)
			return (ft_cd(cmd->argc, cmd->argv, data_env), 1);
		else if (ft_strcmp("export", cmd->argv[0]) == 0 && cmd->argc > 1)
			return (ft_export(cmd->argc, cmd->argv, data_env), 1);
		else if (ft_strcmp("unset", cmd->argv[0]) == 0)
			return (ft_unset(cmd->argc, cmd->argv, data_env), 1);
		else if (ft_strcmp("exit", cmd->argv[0]) == 0)
			return (ft_exit(cmd->argc, cmd->argv), 1);
	}
	return (0);
}
