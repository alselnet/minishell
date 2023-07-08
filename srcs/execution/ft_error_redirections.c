/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:03:31 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/08 22:02:30 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_redirections(t_cmd *cmd)
{
	if (cmd->fd_in == -1)
	{
		ft_error_no_such_file(cmd->error_infile);
		ft_exit_exec(1);
	}
	if (cmd->fd_out == -1)
		ft_exit_exec(1);
}
