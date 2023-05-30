/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:01:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/30 16:27:10 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_monitor;

int	define_token_types(t_lexing *ltable, t_data_env *data_env)
{
	g_monitor = define_redirs(ltable, data_env);
	if (g_monitor)
		define_delims(ltable);
	if (g_monitor)
		g_monitor = define_files(ltable, data_env);
	if (g_monitor)
		g_monitor = define_cmds(ltable, data_env);
	if (g_monitor)
		define_args(ltable);
	if (!g_monitor)
		return (0);
	return (1);
}

int	minishell(t_lexing *ltable, t_data_env *data_env)
{
	while (1)
	{
		ltable->input = readline("> ");
		if (!ltable->input || !ltable->input[0])
			return (free_array(data_env->envp), printf("exit\n"));
		g_monitor = create_token_list(ltable, data_env);
		if (g_monitor)
			g_monitor = parse_token_list(ltable, data_env);
		if (g_monitor)
			g_monitor = expand_token_list(ltable, data_env);
		if (g_monitor)
			g_monitor = define_token_types(ltable, data_env);
		// if (g_monitor)
		// 	print_token_list(&ltable->tklist_head);
		// ON VA RAJOUTER L EXEC
		if (g_monitor)
			ft_execute(ltable->tklist_head, data_env);
		if (g_monitor)
			tk_clear(&ltable->tklist_head);
		free(ltable->input);
	}
	return (g_monitor);
}

int	main(int argc, char **argv, char **envp)
{
	t_lexing	ltable;
	t_data_env	data_env;

	data_env.size = ft_compute_env_len(envp);
	data_env.envp = ft_strdup_env(envp);
	init_table(&ltable);
	(void) argv;
	if (argc != 1)
	{
		printf("./minishell doesn't take any arguments\n");
		return (free_array(data_env.envp));
	}
	minishell(&ltable, &data_env);
	return (0);
}
