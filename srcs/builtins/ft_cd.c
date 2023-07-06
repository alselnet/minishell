/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:04:01 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/04 22:38:27 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_without_arg(t_data_env *s_data_env)
{
	char	*new_path;
	int		i;

	i = 0;
	while (s_data_env->envp[i])
	{
		if (ft_strcmp_env("HOME=", s_data_env->envp[i]) == 0)
			break ;
		i++;
	}
	if (s_data_env->envp[i] != NULL)
		new_path = s_data_env->envp[i] + 5;
	else
	{
		g_minishell.exit_status = 1;
		write(2, "cd: HOME not set\n", 17);
		return (-1);
	}
	if (chdir(new_path) != 0)
	{
		g_minishell.exit_status = 1;
		return (perror("cd: chdir"), -1);
	}
	return (0);
}

void	ft_cd_too_many_args(void)
{
	write(2, "cd: too many arguments\n", 23);
	g_minishell.exit_status = 1;
}

int	ft_go_to_dir(int argc, char **argv, t_data_env *s_data_env)
{
	if (argc == 1)
	{
		if (ft_cd_without_arg(s_data_env) == -1)
			return (-1);
	}
	else
	{
		if (chdir(argv[1]) != 0)
		{
			perror("cd: chdir");
			g_minishell.exit_status = 1;
			return (-1);
		}
	}
	return (0);
}

void	ft_cd(int argc, char **argv, t_data_env *s_data_env)
{
	char	*pwd;

	g_minishell.exit_status = 0;
	if (argc > 2)
	{
		ft_cd_too_many_args();
		return ;
	}
	if (access(argv[1], F_OK) == -1)
	{
		perror("cd");
		g_minishell.exit_status = 1;
		return ;
	}
	if (ft_update_oldpwd(s_data_env) == -1)
		return ;
	if (ft_go_to_dir(argc, argv, s_data_env) == -1)
		return ;
	pwd = ft_get_pwd(argv, s_data_env->envp);
	if (pwd == NULL)
		ft_error(1);
	ft_update_pwd(pwd, s_data_env);
}
