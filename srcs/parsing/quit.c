/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:41:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/10 20:06:38 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free (arr);
	return (0);
}

void	set_error(int error_code)
{
	g_minishell.exit_status = error_code;
}

int	free_structs(t_lexing *ltable, t_data_env *data_env,
			char *error_msg,	char mode)
{
	tk_clear(&ltable->tklist_head);
	if (mode == 1)
		set_error(2);
	if (mode == 2 || mode == 4 || mode == 5)
	{
		set_error(2);
		free_array(data_env->envp);
	}
	ft_putstr_fd(error_msg, 2);
	if (mode == 3 || mode == 4 || mode == 5)
	{
		free(g_minishell.pwd);
		exit(12);
	}
	return (0);
}

void	free_heredoc(t_lexing *ltable, t_data_env *data_env,
			char *error_msg)
{
	tk_clear(&ltable->tklist_head);
	free_array(data_env->envp);
	free(g_minishell.pwd);
	ft_putstr_fd(error_msg, 2);
	exit(g_minishell.exit_status);
}
