/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:05:57 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/22 00:39:38 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_commands.h"

void ft_unset(int argc, char **argv, t_data_env *s_data_env)
{
	int i;
	int var_len;

	i = 0;
	// unset command without argument remove all the environment variables
	if (argc == 2)
	{
		while (s_data_env->envp[i])
		{
			free(s_data_env->envp[i]);
			s_data_env->envp[i++] = NULL;
		}
		return ;
	}
	// unset command with a argument, remove only the variable mentionned in the argument
	// Check that the variable identifier has a correct format
	while (argv[2][i])
	{
		if (ft_isalnum(argv[2][i]) == 0)
		{
			printf("unset: '%s': not a valid identifier\n", argv[2]);
			return ;
		}
		i++;
	}
	// the variable has a correct format
	i = 0;
	var_len = ft_strlen(argv[2]);
	while (s_data_env->envp[i])
	{
		if (ft_strncmp(argv[2], s_data_env->envp[i], var_len) == 0)
			break ;
		i++;
	}
	if (s_data_env->envp[i] == NULL)
		return ;
	else
	{
		ft_remove_var_in_env(i, s_data_env);
	}	
	// // Check that the variable(s) has been removed 
	// if (s_data_env->envp[i] == NULL)
	// 	return ;
	// i = 0;
	// while(s_data_env->envp[i])
	// 	printf("%s\n", s_data_env->envp[i++]);
}