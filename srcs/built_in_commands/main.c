/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:01:36 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/22 00:38:44 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in_commands.h"

int	main (int argc, char **argv, char **envp)
{
	t_data_env	*s_data_env;
	
	s_data_env = (t_data_env *)malloc(sizeof(t_data_env));
	s_data_env->size = ft_compute_env_len(envp);
	s_data_env->envp = ft_strdup_env(envp);
	if (ft_strcmp("cd", argv[1]) == 0)
		ft_cd(argc, argv);
	else if (ft_strcmp("pwd", argv[1]) == 0)
		ft_pwd();
	else if (ft_strcmp("unset", argv[1]) == 0)
		ft_unset(argc, argv, s_data_env);
	else if (ft_strcmp("env", argv[1]) == 0)
		ft_env(envp);
	else if (ft_strcmp("export", argv[1]) == 0)
		ft_export(argc, argv, s_data_env);

	// Check your environment
	if (ft_strcmp("unset", argv[1]) == 0)
		ft_print_env(s_data_env);
	else if ((ft_strcmp("export", argv[1]) == 0) && (argc != 2))
		ft_print_env(s_data_env);
	return (0);
}