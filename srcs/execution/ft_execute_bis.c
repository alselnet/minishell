/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:28:04 by orazafy           #+#    #+#             */
/*   Updated: 2023/06/29 09:14:43 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_std_backup(t_data_env *data_env)
{
	data_env->stdin = dup(STDIN_FILENO);
	if (data_env->stdin == -1)
		ft_error(1);
	data_env->stdout = dup(STDOUT_FILENO);
	if (data_env->stdout == -1)
		ft_error(1);
}

void	ft_set_stdin_to_null(int builtin_done)
{
	int	null_fd;

	if (builtin_done == 1)
	{
		null_fd = open("/dev/null", O_RDONLY);
		if (dup2(null_fd, STDIN_FILENO) == -1)
		{
			close(null_fd);
			ft_error(1);
		}
		close(null_fd);
	}
}

int	ft_init_pipe_before(t_cmd *cmd)
{
	if (cmd->pipe == 1)
		return (1);
	else
		return (0);
}

void	ft_restore_before_next_prompt(t_data_env *data_env, t_cmd *cmd)
{
	if (dup2(data_env->stdin, STDIN_FILENO) == -1)
		ft_error(1);
	ft_close(&data_env->stdin);
	if (dup2(data_env->stdout, STDOUT_FILENO) == -1)
		ft_error(1);
	ft_close(&data_env->stdout);
	ft_close_all_fds();
	unlink(".hdoc.txt");
	ft_free_cmd(cmd);
}
