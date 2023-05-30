/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:01:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/30 19:03:40 by orazafy          ###   ########.fr       */
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
		add_history(ltable->input);
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

void	handler_function(int signum, siginfo_t *siginfo, void *ptr)
{
	(void)ptr;
	(void)siginfo;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_lexing			ltable;
	t_data_env			data_env;
	struct sigaction	sa;

	sa.sa_sigaction = handler_function;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa, 0) == -1)
	//handle error
		exit(1);
	if (sigaction(SIGQUIT, &sa, 0) == -1)
	//handle error
		exit(1);
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
