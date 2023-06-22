/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:01:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/06/22 13:33:20 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	define_token_types(t_lexing *ltable, t_data_env *data_env)
{
	g_minishell.monitor = define_redirs(ltable, data_env);
	if (g_minishell.monitor)
		define_delims(ltable);
	if (g_minishell.monitor)
		g_minishell.monitor = define_files(ltable, data_env);
	if (g_minishell.monitor)
		g_minishell.monitor = define_cmds(ltable, data_env);
	if (g_minishell.monitor)
		define_args(ltable);
	if (!g_minishell.monitor)
		return (0);
	return (1);
}

int	minishell(t_lexing *ltable, t_data_env *data_env)
{
	while (1)
	{
		ltable->input = readline("> ");
		if (!ltable->input)
			return (rl_clear_history(), free_array(data_env->envp), printf("exit\n"));
			// return (free_array(data_env->envp), printf("exit\n"));
		if (ltable->input[0] == 0)
			continue ;
		add_history(ltable->input);
		g_minishell.monitor = create_token_list(ltable, data_env);
		if (g_minishell.monitor)
			g_minishell.monitor = parse_token_list(ltable, data_env);
		if (g_minishell.monitor)
			g_minishell.monitor = expand_token_list(ltable, data_env);
		if (g_minishell.monitor)
			g_minishell.monitor = define_token_types(ltable, data_env);
		// if (g_minishell.monitor)
		// 	print_token_list(&ltable->tklist_head);
		if (g_minishell.monitor)
			ft_execute(ltable->tklist_head, data_env);
		if (g_minishell.monitor)
			tk_clear(&ltable->tklist_head);
		free(ltable->input);
	}
	return (g_minishell.monitor);
}

int	main(int argc, char **argv, char **envp)
{
	if (envp == NULL)
		return (1);
	if (envp[0] == NULL)
		return (1);
	ft_init_signals();
	ft_init_g_minishell(&g_minishell, envp);
	(void) argv;
	if (argc != 1)
	{
		write(2, "./minishell doesn't take any arguments\n", 39);
		return (free_array(g_minishell.data_env.envp));
	}
	minishell(&g_minishell.ltable, &g_minishell.data_env);
	return (0);
}
