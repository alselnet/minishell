/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:01:36 by orazafy           #+#    #+#             */
/*   Updated: 2023/05/26 00:51:21 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_minishell	g_minishell;

void	ft_init_data_env(t_data_env *s_data_env, char **envp)
{
	s_data_env->size = ft_compute_env_len(envp);
	s_data_env->envp = ft_strdup_env(envp);
	if (s_data_env->envp == NULL)
		ft_error("Failed to allocate the requested memory", s_data_env);
}

char	**ft_adapt_argv(char **argv, int argc)
{
	int		i;
	char	**result;

	i = 0;
	result = (char **)malloc(sizeof(char *) * argc);
	while (i < argc)
	{
		result[i] = ft_strdup(argv[i + 1]);
		i++;
	}
	return (result);
}

void	ft_free(char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	ft_print_env(t_data_env *s_data_env)
{
	int	i;

	i = 0;
	while (s_data_env->envp[i])
		printf("%s\n", s_data_env->envp[i++]);
}

int	main(int argc, char **argv, char **envp)
{
	t_data_env	s_data_env;

	argc--;
	argv = ft_adapt_argv(argv, argc);
	g_minishell.exit_status = 0;
	ft_init_data_env(&s_data_env, envp);
	if (ft_strcmp("cd", argv[0]) == 0)
		ft_cd(argc, argv, &s_data_env);
	else if (ft_strcmp("pwd", argv[0]) == 0)
		ft_pwd();
	else if (ft_strcmp("unset", argv[0]) == 0)
		ft_unset(argc, argv, &s_data_env);
	else if (ft_strcmp("env", argv[0]) == 0)
		ft_env(envp);
	else if (ft_strcmp("export", argv[0]) == 0)
		ft_export(argc, argv, &s_data_env);
	else if (ft_strcmp("echo", argv[0]) == 0)
		ft_echo(argc, argv);
	ft_free_env(s_data_env.envp, s_data_env.size);
	ft_free(argv, argc);
	return (0);
}

// 	// Check your environment
// 	if (ft_strcmp("unset", argv[0]) == 0)
// 		ft_print_env(&s_data_env);
// 	else if ((ft_strcmp("export", argv[0]) == 0) && (argc != 1))
// 		ft_print_env(&s_data_env);
// 	else if (ft_strcmp("cd", argv[0]) == 0)
// 		ft_print_env(&s_data_env);
// 	// Check for leaks
// 	// ft_print_env(&s_data_env);
// 	ft_free_env(s_data_env.envp, s_data_env.size);
// 	ft_free(argv, argc);

// 	// Check exit status
// 	printf("EXIT STATUS: %d\n", g_minishell.exit_status);
// 	return (0);
// }