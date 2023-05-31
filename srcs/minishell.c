/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:01:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/31 19:26:53 by orazafy          ###   ########.fr       */
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
			return (free_array(data_env->envp), printf("exit\n"));
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
		// ON VA RAJOUTER L EXEC
		if (g_minishell.monitor)
			ft_execute(ltable->tklist_head, data_env);
		if (g_minishell.monitor)
			tk_clear(&ltable->tklist_head);
		free(ltable->input);
	}
	return (g_minishell.monitor);
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
		g_minishell.exit_status = 1;
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
