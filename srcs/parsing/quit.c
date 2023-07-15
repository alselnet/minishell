/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:41:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/15 19:09:22 by orazafy          ###   ########.fr       */
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
	g_mini.exit_status = error_code;
}

int	free_structs(t_lexing *ltable, t_data_env *data_env,
			char *error_msg,	char mode)
{
	tk_clear(&ltable->tklist_head);
	if (mode == 1)
	{
		ft_putstr_fd(error_msg, 2);
		//exit(2); // for testing
	}
	//	set_error(2);
	if (mode == 2 || mode == 4 || mode == 5)
	{
		set_error(2);
		ft_free_env(data_env->envp, data_env->size);
		//exit(2);//for testing
	}
	ft_putstr_fd(error_msg, 2);
	if (mode == 3 || mode == 4 || mode == 5)
	{
		free(data_env->pwd);
		exit(12);
	}
	return (0);
}
