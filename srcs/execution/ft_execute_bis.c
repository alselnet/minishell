/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:28:04 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/15 17:07:36 by orazafy          ###   ########.fr       */
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

int	ft_init_pipe_before(t_cmd *cmd)
{
	if (cmd->pipe == 1)
		return (1);
	else
		return (0);
}

void	ft_restore_before_next_prompt(t_minishell *mini)
{
	t_data_env *data_env;

	data_env = &mini->data_env;
	if (dup2(data_env->stdin, STDIN_FILENO) == -1)
		ft_error(1);
	ft_close(&data_env->stdin);
	if (dup2(data_env->stdout, STDOUT_FILENO) == -1)
		ft_error(1);
	ft_close(&data_env->stdout);
	ft_close_all_fds(mini);
	unlink("/tmp/.hdoc.txt");
	ft_free_cmd(&mini->cmd);
	g_mini.inside_heredoc = 0;
}
