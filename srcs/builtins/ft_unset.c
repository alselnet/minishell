/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:05:57 by orazafy           #+#    #+#             */
/*   Updated: 2023/06/05 17:37:53 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_without_arg(t_data_env *s_data_env)
{
	int	i;

	i = 0;
	while (s_data_env->envp[i])
	{
		free(s_data_env->envp[i]);
		s_data_env->envp[i++] = NULL;
	}
	s_data_env->size = 0;
	g_minishell.exit_status = 0;
}

int	ft_check_var_format_unset(char **argv, int *j)
{
	int	is_broken;
	int	i;

	is_broken = 0;
	i = 0;
	while (argv[*j][i])
	{
		if (ft_isalnum(argv[*j][i]) == 0 && (argv[*j][i] != '_'))
		{
			ft_error_identifier("unset", argv[*j]);
			g_minishell.exit_status = 1;
			is_broken = 1;
			break ;
		}
		i++;
	}
	if (is_broken == 1)
	{
		(*j)++;
		return (-1);
	}
	return (0);
}

int	ft_unset_with_arg(char **argv, t_data_env *s_data_env, int j)
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
		return (0);
	return (ft_remove_var_in_env(i, s_data_env));
}

void	ft_unset(int argc, char **argv, t_data_env *s_data_env)
{
	int	j;

	g_minishell.exit_status = 0;
	if (argc == 1)
	{
		ft_unset_without_arg(s_data_env);
		return ;
	}
	j = 1;
	while (j < argc)
	{
		if (ft_check_var_format_unset(argv, &j) == -1)
			continue ;
		if (ft_unset_with_arg(argv, s_data_env, j) == -1)
			ft_error(1);
		j++;
	}
}
