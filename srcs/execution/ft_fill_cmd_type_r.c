/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd_type_r.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 22:46:28 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/08 22:01:59 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_cmd_for_type_r(t_cmd *cmd, t_token *lst)
{
	if (lst->content[0] == '<')
	{
		if (cmd->fd_in == -1)
			return ;
		if (cmd->fd_in != -2)
			close(cmd->fd_in);
		if (lst->content[1] == '<')
		{
			cmd->fd_in = open(".hdoc.txt", O_RDONLY, 0500);
			if (cmd->fd_in == -1)
				ft_error(1);
		}
		else
		{
			cmd->fd_in = open(lst->next->content, O_RDONLY, 0500);
			if (cmd->fd_in == -1)
				cmd->error_infile = lst->next->content;
		}
	}
	ft_fill_cmd_for_type_r2(cmd, lst);
}

void	ft_fill_cmd_for_type_r2(t_cmd *cmd, t_token *lst)
{
	char	*outfile;

	outfile = lst->next->content;
	if (lst->content[0] == '>')
	{
		if (cmd->fd_out == -1)
			return ;
		if (cmd->fd_out != -2)
			close(cmd->fd_out);
		if (lst->content[1] == '>')
			cmd->fd_out = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0664);
		else
			cmd->fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (cmd->fd_out == -1 && cmd->fd_in != -1)
		{
			perror("");
			g_minishell.exit_status = 1;
		}
	}
}
