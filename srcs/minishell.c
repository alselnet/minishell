/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:01:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/04 14:12:36 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

int	define_token_types(t_lexing *ltable, t_data_env *data_env)
{
	if (!join_quotes(ltable, data_env))
		return (0);
	g_minishell.monitor = define_redirs(ltable);
	if (g_minishell.monitor)
		define_delims(ltable);
	if (g_minishell.monitor)
		g_minishell.monitor = define_files(ltable);
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
		g_minishell.status_done = 0;
		ltable->input = readline("minishell$ ");
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
			g_minishell.monitor = parse_redirections(ltable, data_env);
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
		free_array(g_minishell.data_env.envp);
		return (127);
	}
	minishell(&g_minishell.ltable, &g_minishell.data_env);
	return (0);
}
