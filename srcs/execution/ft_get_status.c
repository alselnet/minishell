/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 18:42:15 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/10 18:47:37 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_status(int status)
{
	if (WIFEXITED(status))
	{
		g_minishell.exit_status = WEXITSTATUS(status);
		g_minishell.status_done = 1;
	}
	if (WIFSIGNALED(status))
	{
		g_minishell.exit_status = 128 + WTERMSIG(status);
		g_minishell.status_done = 1;
	}
}
