/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:05:57 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/23 19:53:15 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_commands.h"

void ft_unset(int argc, char **argv, t_data_env *s_data_env)
{
	int i;
	int	j;
	int var_len;

	// unset command without argument remove all the environment variables
	if (argc == 2)
	{
		i = 0;
		while (s_data_env->envp[i])
		{
			free(s_data_env->envp[i]);
			s_data_env->envp[i++] = NULL;
		}
		s_data_env->size = 0;
		return ;
	}
	j = 2;
	while (j < argc)
	{
		i = 0;
			// unset command with a argument, remove only the variable mentionned in the argument
		// Check that the variable identifier has a correct format
		while (argv[j][i])
		{
			if (ft_isalnum(argv[j][i]) == 0 && (argv[j][i] != '_'))
			{
				printf("unset: '%s': not a valid identifier\n", argv[j]);
				return ;
			}
			i++;
		}
		// the variable has a correct format
		i = 0;
		var_len = ft_strlen(argv[j]);
		while (s_data_env->envp[i])
		{
			if (ft_strncmp(argv[j], s_data_env->envp[i], var_len) == 0)
				break ;
			i++;
		}
		if (s_data_env->envp[i] == NULL)
			return ;
		else
			ft_remove_var_in_env(i, s_data_env);
		j++;
	}
	
	// // Check that the variable(s) has been removed 
	// if (s_data_env->envp[i] == NULL)
	// 	return ;
	// i = 0;
	// while(s_data_env->envp[i])
	// 	printf("%s\n", s_data_env->envp[i++]);
}