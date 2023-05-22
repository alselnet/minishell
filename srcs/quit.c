/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:41:50 by aselnet           #+#    #+#             */
/*   Updated: 2023/05/22 17:41:59 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	free_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
	free (arr);
	return (0);
}

void	quit(t_lexing *ltable, char *error_msg,	char mode)
{
	if (mode == 1)
		tk_clear(&ltable->tklist_head);
	perror(error_msg);
	exit(EXIT_FAILURE);
}