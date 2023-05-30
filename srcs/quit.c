/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:41:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/30 16:27:17 by orazafy          ###   ########.fr       */
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

int	free_structs(t_lexing *ltable, t_data_env *data_env,
			char *error_msg,	char mode)
{
	if (mode == 1 || mode == 2)
		tk_clear(&ltable->tklist_head);
	if (mode == 2)
		free_array(data_env->envp);
	ft_putstr_fd(error_msg, 2);
	return (0);
}
