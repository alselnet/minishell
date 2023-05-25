/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:49:58 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/25 18:51:20 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_update_oldpwd_utils(t_data_env *s_data_env, char *oldpwd)
{
	int	i;

	i = 0;
	while (s_data_env->envp[i])
	{
		if (ft_strcmp_env("OLDPWD=", s_data_env->envp[i]) == 0)
			break ;
		i++;
	}
	if (s_data_env->envp[i] != NULL)
	{
		free(s_data_env->envp[i]);
		s_data_env->envp[i] = oldpwd;
	}
	else
	{
		s_data_env->envp = ft_add_var_env(s_data_env, oldpwd);
		free(oldpwd);
		if (s_data_env->envp == NULL)
			ft_error("Failed to allocate the requested memory", s_data_env);
	}
	return (0);
}

int	ft_update_oldpwd(t_data_env *s_data_env)
{
	char	current_path[1000];
	char	*oldpwd;

	if (getcwd(current_path, sizeof(current_path)) == NULL)
	{
		perror("");
		g_minishell.exit_status = 1;
		return (-1);
	}
	oldpwd = ft_strjoin("OLDPWD=", current_path);
	if (oldpwd == NULL)
		ft_error("Failed to allocate the requested memory", s_data_env);
	return (ft_update_oldpwd_utils(s_data_env, oldpwd));
}

void	ft_update_pwd(char *pwd, t_data_env *s_data_env)
{
	int	i;

	i = 0;
	while (s_data_env->envp[i])
	{
		if (ft_strcmp_env("PWD=", s_data_env->envp[i]) == 0)
			break ;
		i++;
	}
	if (s_data_env->envp[i] != NULL)
	{
		free(s_data_env->envp[i]);
		s_data_env->envp[i] = pwd;
	}
	else
	{
		s_data_env->envp = ft_add_var_env(s_data_env, pwd);
		free(pwd);
		if (s_data_env->envp == NULL)
			ft_error("Failed to allocate the requested memory", s_data_env);
	}
}

char	*ft_get_pwd(t_data_env *s_data_env)
{
	char	*pwd;
	char	current_path[1000];

	if (getcwd(current_path, sizeof(current_path)) == NULL)
	{
		perror("");
		g_minishell.exit_status = 1;
		return (NULL);
	}
	pwd = ft_strjoin("PWD=", current_path);
	if (pwd == NULL)
		ft_error("Failed to allocate the requested memory", s_data_env);
	return (pwd);
}
