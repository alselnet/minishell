/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:36:20 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/03 00:27:34 by orazafy          ###   ########.fr       */
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
	while (1)
	{
		ft_init_cmd(&g_minishell.cmd);
		fetch_heredoc(&g_minishell.cmd, tklist_head);
		tklist_head = ft_get_cmd(tklist_head, &g_minishell.cmd);
		builtin_done = ft_exe_builtin1(&g_minishell.cmd, data_env, pipe_before);
		ft_set_stdin_to_null(builtin_done);
		if (builtin_done == 0)
			ft_fork(&g_minishell.cmd, data_env);
		else
			g_minishell.status_done = 1;
		if (g_minishell.cmd.final_cmd == 1)
			break ;
		pipe_before = ft_init_pipe_before(&g_minishell.cmd);
		ft_free_cmd(&g_minishell.cmd);
		builtin_done = 0;
	}
	ft_waitpid(&g_minishell.cmd);
	ft_restore_before_next_prompt(data_env, &g_minishell.cmd);
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
				ft_error(1);
		}
		if (res == -1 && (errno != EINTR && errno != ECHILD))
			ft_error(1);
	}
	return ;
}

int	ft_exe_builtin1(t_cmd *cmd, t_data_env *data_env, int pipe_before)
{
	if (cmd->argv != NULL)
	{
		if (ft_strcmp("cd", cmd->argv[0]) == 0)
			return (ft_exec_cd(pipe_before, cmd, data_env));
		else if (ft_strcmp("unset", cmd->argv[0]) == 0)
			return (ft_exec_unset(pipe_before, cmd, data_env));
		else if (ft_strcmp("export", cmd->argv[0]) == 0 && cmd->argc > 1)
			return (ft_exec_export(pipe_before, cmd, data_env));
		else if (ft_strcmp("exit", cmd->argv[0]) == 0)
			return (ft_exec_exit(pipe_before, cmd));
	}
	return (0);
}
