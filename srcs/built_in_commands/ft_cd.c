/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:04:01 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/23 19:56:00 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_commands.h"

// note: cd at home or at the cwd when we started minishell?

void	ft_cd(int argc, char **argv, t_data_env *s_data_env)
{
	char *new_path;
	char current_path[1000];
	int i;
	char *oldpwd;
	char *pwd;

	// update "OLDPWD" variable
	if (getcwd(current_path, sizeof(current_path)) == NULL)
	{
		perror("");
		return ;
	}
	oldpwd = ft_strjoin("OLDPWD=", current_path);
	if (oldpwd == NULL)
		ft_error("Failed to allocate the requested memory", s_data_env);
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
	// cd without a path
	if (argc == 2)
	{
		new_path = getenv("HOME");
		if (new_path == NULL)
		{
			perror("");
			return ;
		}
		if (chdir(new_path) != 0)
		{
			printf("cd: '%s': No such file or directory\n", argv[2]);
			return ;
		}	
	}
	// cd with a relative or absolute path
	else
	{
		if (chdir(argv[2]) != 0)
		{
			printf("cd: %s: No such file or directory\n", argv[2]);
			return ;
		}
	}
	// get new current path
	if (getcwd(current_path, sizeof(current_path)) == NULL)
	{
		perror("");
		return ;
	}
	pwd = ft_strjoin("PWD=", current_path);
	if (pwd == NULL)
	{
		free(oldpwd);
		ft_error("Failed to allocate the requested memory", s_data_env);
	}	
	// update PWD variable
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
	// Check that we get the right directory now	
	getcwd(current_path, sizeof(current_path));
	printf("NOW WE HARE IN THIS DIRECTORY: %s\n", current_path);
	ft_env(s_data_env->envp);
}