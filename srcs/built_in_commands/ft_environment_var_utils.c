/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_environment_var_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:10:58 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/23 19:35:09 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_commands.h"

int	ft_strcmp_env(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i] && s1[i] != '=' && s2[i] != '=')
		i++;
	if (s1[i] == '=' && s2[i] != '=')
		return (-1);
	if (s2[i] == '=' && s1[i] != '=')
		return (1);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_compute_env_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return(i);
}

void	ft_remove_var_in_env(int i, t_data_env *s_data_env)
{
	char **envp;
	
	envp = s_data_env->envp;
	while (1)
	{
		free(envp[i]);
		if (envp[i + 1] != NULL)
		{
			envp[i] = ft_strdup(envp[i + 1]);
			if (envp[i] == NULL)
				return (ft_free_env(envp, i));
		}
		else
			envp[i] = NULL;
		if (envp[i] == NULL)
			break ;
		i++;
	}
	s_data_env->size--;
}

char	**ft_strdup_env(char **envp)
{
	int	size;
	char **env;
	int	i;
	
	size = ft_compute_env_len(envp);
	env = (char **)malloc(sizeof(char *) * (size + 1));
	if (env == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (env[i] == NULL)
		{
			ft_free_env(env, i);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}

void	ft_print_env(t_data_env *s_data_env)
{
	int i;
	
	i = 0;
	while (s_data_env->envp[i])
		printf("%s\n", s_data_env->envp[i++]);
}

char	**ft_add_var_env(t_data_env *s_data_env, char *new_var)
{
	char	**dup_env;
	int		i;
		
	i = 0;
	dup_env = (char **)malloc(sizeof(char *) * (s_data_env->size + 2));
	if (dup_env == NULL)
		return (NULL);
	while (s_data_env->envp[i])
	{
		dup_env[i] = ft_strdup(s_data_env->envp[i]);
		if (dup_env[i] == NULL)
			return (ft_free_env(dup_env, i), NULL);
		free(s_data_env->envp[i]);
		i++;
	}
	free(s_data_env->envp[i]);
	free(s_data_env->envp);
	dup_env[i++] = ft_strdup(new_var);
	if (dup_env[i - 1] == NULL)
		return (ft_free_env(dup_env, i - 1), NULL);
	dup_env[i] = NULL;
	s_data_env->size++;
	return (dup_env);
}

void	ft_free_env(char **env, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (env[i] != NULL)
			free(env[i]);
		i++;
	}
	if (env != NULL)
		free(env);
}