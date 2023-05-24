/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:01:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/24 15:51:13 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	minishell(t_lexing *ltable, t_data_env *data_env)
{
	int	monitor;

	while (1)
	{
		ltable->input = readline("> ");
		if (!ltable->input || !ltable->input[0])
			return (free_array(data_env->envp), printf("exit\n"));
		monitor = create_token_list(ltable, data_env);
		if (monitor)
			monitor = parse_token_list(ltable, data_env);
		if (monitor)
			monitor = expand_token_list(ltable, data_env);
		if (monitor)
			monitor = define_token_types(ltable, data_env);
		if (monitor)
			print_token_list(&ltable->tklist_head);
		if (monitor)
			tk_clear(&ltable->tklist_head);
		free(ltable->input);
	}
	return (monitor);
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
