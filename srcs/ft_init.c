/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 19:18:39 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/04 12:05:51 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_data_env(t_data_env *s_data_env, char **envp)
{
	s_data_env->size = ft_compute_env_len(envp);
	s_data_env->envp = ft_strdup_env(envp, 0);
	if (s_data_env->envp == NULL)
	{
		perror("");
		ft_free_env(s_data_env->envp, s_data_env->size);
		exit(EXIT_FAILURE);
	}
	s_data_env->stdin = -2;
	s_data_env->stdout = -2;
}

void	ft_init_g_minishell(t_minishell *g_minishell, char **envp)
{
	g_minishell->exit_status = 0;
	g_minishell->monitor = 0;
	g_minishell->status_done = 0;
	ft_init_data_env(&g_minishell->data_env, envp);
	init_table(&g_minishell->ltable);
}

void	init_table(t_lexing *ltable)
{
	ltable->tklist_head = 0;
	ltable->input = 0;
	ltable->tklist_size = 0;
}
