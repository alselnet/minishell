/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:08:01 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/25 19:40:48 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_export_without_arg(t_data_env *s_data_env)
{
	int		i;
	char	**dup_env;
	int		min;

	dup_env = ft_strdup_env(s_data_env->envp);
	if (dup_env == NULL)
	{
		g_minishell.exit_status = 1;
		return ;
	}	
	i = 0;
	while (i < s_data_env->size)
	{
		min = ft_print_env_min(dup_env, s_data_env->size);
		free(dup_env[min]);
		dup_env[min] = NULL;
		i++;
	}
	free(dup_env[i]);
	free(dup_env);
}

void	ft_export_with_arguments(char **argv, t_data_env *s_data_env, int j)
{
	int	i;

	i = 0;
	while (s_data_env->envp[i])
	{
		if (ft_strcmp_env(argv[j], s_data_env->envp[i]) == 0)
			break ;
		i++;
	}
	if (s_data_env->envp[i] == NULL)
	{
		s_data_env->envp = ft_add_var_env(s_data_env, argv[j]);
		if (s_data_env->envp == NULL)
			ft_error("Failed to allocate the requested memory", s_data_env);
	}	
	else
	{
		free(s_data_env->envp[i]);
		s_data_env->envp[i] = NULL;
		s_data_env->envp[i] = ft_strdup(argv[j]);
		if (s_data_env->envp[i] == NULL)
			ft_error("Failed to allocate the requested memory", s_data_env);
	}
}

void	ft_export(int argc, char **argv, t_data_env *s_data_env)
{
	int	j;

	g_minishell.exit_status = 0;
	if (argc == 1)
	{
		ft_export_without_arg(s_data_env);
		return ;
	}
	j = 1;
	while (j < argc)
	{
		if (ft_check_var_format_export(argv, &j) == -1)
			continue ;
		if (ft_srch('=', argv[j]) >= 1)
			ft_export_with_arguments(argv, s_data_env, j);
		j++;
	}
}
