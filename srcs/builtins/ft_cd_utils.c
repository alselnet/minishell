/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 18:49:58 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/08 16:32:44 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_oldpwd_utils(t_data_env *s_data_env, char *oldpwd)
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
		if (g_minishell.oldpwd_done != 1)
		{
			s_data_env->envp = ft_add_var_env(s_data_env, oldpwd);
			free(oldpwd);
			if (s_data_env->envp == NULL)
				ft_error(200);
		}
		g_minishell.oldpwd_done = 1;
	}
}

int	ft_update_oldpwd(t_data_env *s_data_env)
{
	char	current_path[1000];
	char	*oldpwd;
	char	*pwd;

	if (g_minishell.pwd != NULL)
		pwd = g_minishell.pwd;
	else
		pwd = ft_retrieve_pwd_env(s_data_env->envp);
	if (pwd == NULL)
	{
		if (getcwd(current_path, sizeof(current_path)) == NULL)
			return (perror("cd: getcwd"), -1);
		oldpwd = ft_strjoin("OLDPWD=", current_path);
		if (oldpwd == NULL)
			ft_error(200);
	}
	else
	{
		oldpwd = ft_strjoin("OLDPWD=", pwd);
		if (oldpwd == NULL)
			ft_error(200);
	}
	ft_update_oldpwd_utils(s_data_env, oldpwd);
	return (0);
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
		free(pwd);
}

char	*ft_get_pwd(char **argv, char **envp)
{
	char	*pwd;
	char	current_path[1000];
	char	*pwd_env;
	char	*pwd_slash;

	if (getcwd(current_path, sizeof(current_path)) == NULL)
	{
		perror("cd: getcwd");
		if (g_minishell.pwd != NULL)
			pwd_env = ft_strjoin("PWD=", g_minishell.pwd);
		else
			pwd_env = ft_strjoin("PWD=", ft_retrieve_pwd_env(envp));
		if (pwd_env == NULL)
			ft_error(200);
		pwd_slash = ft_strjoin(pwd_env, "/");
		if (pwd_slash == NULL)
			return (free(pwd_env), NULL);
		free(pwd_env);
		pwd = ft_strjoin(pwd_slash, argv[1]);
		free(pwd_slash);
	}
	else
		pwd = ft_strjoin("PWD=", current_path);
	return (pwd);
}
