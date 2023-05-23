/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:08:01 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/23 19:40:02 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_commands.h"

void	ft_print_export(char *str)
{
	while (*str != '=')
		printf("%c", *(str++));
	printf("%c\"", *str);
	str++;
	while (*str)
		printf("%c", *(str++));
	printf("\"\n");
}

int ft_print_env_min(char **env, int size)
{
	int	i;
	char *min;
	int	pos_min;

	i = 0;
	while (i < size)
	{
		if (env[i] != NULL)
		{
			min = env[i];
			pos_min = i;
			break ;
		}
		i++;
	}
	i = 0;
	while(i < size)
	{
		if (env[i] == NULL)
		{
			i++;
			continue ;
		}
		if (ft_strcmp_env(env[i], min) < 0)
		{
			min = env[i];
			pos_min = i;
		}	
		i++;
	}
	printf("declare -x ");
	ft_print_export(min);
	return(pos_min);
}

void	ft_export_without_arg(t_data_env *s_data_env)
{
	int	i;
	char **dup_env;
	int min;
	
	dup_env = ft_strdup_env(s_data_env->envp);
	if (dup_env == NULL)
		return ;
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

// TO HANDLE
/*
> When the parsing will be done, 
the loop will be different

It will be someting like as long as it is WORD, loop through each word

*/

void ft_export(int argc, char **argv, t_data_env *s_data_env)
{
	int i;
	int j;
	
	// export without any argument
	if (argc == 2)
	{
		ft_export_without_arg(s_data_env);
		return ;
	}
	j = 2;
	while (j < argc)
	{
		// export with an argument
		// Check that the variable identifier has a correct format
		if (ft_srch('=', argv[j]) == 0)
		{
			printf("export: '%s': not a valid identifier\n", argv[j]);
			return ;
		}
		i = 0;
		while (argv[j][i] && argv[j][i] != '=')
		{
			if (ft_isalnum(argv[j][i]) == 0 && (argv[j][i] != '_'))
			{
				printf("export: '%s': not a valid identifier\n", argv[j]);
				return ;
			}
			i++;
		}
		// the argument must have a '=' at least at the 2nd character
		if (ft_srch('=', argv[j]) >= 1)
		{
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
		j++;
	}
}