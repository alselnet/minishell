/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_ter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:30:25 by orazafy           #+#    #+#             */
/*   Updated: 2023/06/22 13:27:00 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_cd_utils(t_cmd *cmd, t_data_env *data_env)
{
	int	i;

	i = 0;
	if (cmd->argc == 1)
	{
		while (data_env->envp[i])
		{
			if (ft_strcmp_env("HOME=", data_env->envp[i]) == 0)
				break ;
			i++;
		}
		if (data_env->envp[i] == NULL)
		{
			g_minishell.exit_status = 1;
			write(2, "cd: HOME not set\n", 17);
		}
	}
	else
	{
		if (access(cmd->argv[1], F_OK) == -1)
		{
			ft_error_file("cd", cmd->argv[1]);
			g_minishell.exit_status = 1;
		}
	}
}

int	ft_exec_cd(int pipe_before, t_cmd *cmd, t_data_env *data_env)
{
	if (pipe_before != 1 && cmd->pipe != 1)
		ft_cd(cmd->argc, cmd->argv, data_env);
	else
	{
		g_minishell.exit_status = 0;
		if (cmd->argc > 2)
			ft_cd_too_many_args();
		ft_exec_cd_utils(&g_minishell.cmd, data_env);
	}
	return (1);
}

int	ft_exec_unset(int pipe_before, t_cmd *cmd, t_data_env *data_env)
{
	int	j;

	if (pipe_before != 1 && cmd->pipe != 1)
		ft_unset(cmd->argc, cmd->argv, data_env);
	else
	{
		j = 1;
		g_minishell.exit_status = 0;
		while (j < cmd->argc)
		{
			if (ft_check_var_format_unset(cmd->argv, &j) == -1)
				continue ;
			j++;
		}
	}	
	return (1);
}

int	ft_exec_export(int pipe_before, t_cmd *cmd, t_data_env *data_env)
{
	int	j;

	if (pipe_before != 1 && cmd->pipe != 1)
		ft_export(cmd->argc, cmd->argv, data_env);
	else
	{
		j = 1;
		g_minishell.exit_status = 0;
		while (j < cmd->argc)
		{
			if (ft_check_var_format_export(cmd->argv, &j) == -1)
				continue ;
			j++;
		}
	}
	return (1);
}

int	ft_exec_exit(int pipe_before, t_cmd *cmd)
{
	if (pipe_before != 1 && cmd->pipe != 1)
		ft_exit(cmd->argc, cmd->argv);
	if (cmd->argc > 2 && (pipe_before == 1 || cmd->pipe == 1))
	{
		if (ft_check_numeric_arg(cmd->argv, 1) == -1)
			return (1);
		write(2, "exit: too many arguments\n", 25);
		g_minishell.exit_status = 1;
	}
	else if (cmd->argc == 2 && (pipe_before == 1 || cmd->pipe == 1))
	{
		if (ft_check_numeric_arg(cmd->argv, 1) == -1)
			return (1);
		g_minishell.exit_status = ft_atoi_exit(cmd->argv[1]);
	}
	return (1);
}
