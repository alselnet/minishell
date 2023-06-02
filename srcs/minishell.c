/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:01:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/06/02 18:24:12 by orazafy          ###   ########.fr       */
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
		if (g_minishell.monitor)
			ft_execute(ltable->tklist_head, data_env);
		if (g_minishell.monitor)
			tk_clear(&ltable->tklist_head);
		free(ltable->input);
	}
	return (g_minishell.monitor);
}

// Take exactly this one (I need this version for builtins)
void	ft_free_env(char **env, int size)
{
	int	i;

	i = 0;
	if (env == NULL)
		return ;
	while (i < size)
	{
		if (env[i] != NULL)
		{
			free(env[i]);
			env[i] = NULL;
		}
		i++;
	}
	free(env);
}

// it's the builtin version, may need to adapt later or change inside builtins
void	ft_error_envp(char *error_msg, t_data_env *s_data_env)
{
	perror(error_msg);
	ft_free_env(s_data_env->envp, s_data_env->size);
	g_minishell.exit_status = 1;
	exit(EXIT_FAILURE);
}

void	ft_init_data_env(t_data_env *s_data_env, char **envp)
{
	s_data_env->size = ft_compute_env_len(envp);
	s_data_env->envp = ft_strdup_env(envp);
	if (s_data_env->envp == NULL)
		ft_error_envp("Failed to allocate the requested memory", s_data_env);
	s_data_env->stdin_closed = -1;
	s_data_env->stdout_closed = -1;
}

void	ft_init_g_minishell(t_minishell *g_minishell, char **envp)
{
	g_minishell->exit_status = 0;
	g_minishell->monitor = 0;
	ft_init_data_env(&g_minishell->data_env, envp);
	init_table(&g_minishell->ltable);
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

void	ft_init_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handler_function;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sa, 0) == -1)
		exit(1);
	if (sigaction(SIGQUIT, &sa, 0) == -1)
		exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	ft_init_signals();
	ft_init_g_minishell(&g_minishell, envp);
	(void) argv;
	if (argc != 1)
	{
		printf("./minishell doesn't take any arguments\n");
		return (free_array(g_minishell.data_env.envp));
	}
	minishell(&g_minishell.ltable, &g_minishell.data_env);
	return (0);
}
