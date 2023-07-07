/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:59:34 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/07 19:07:21 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_get_cmd(t_token *tklist_head, t_cmd *cmd, int pipe_before)
{
	t_token	*lst;

	lst = tklist_head;
	while (lst != NULL)
	{
		if (lst->content[0] == '|')
			break ;
		ft_fill_cmd(cmd, lst);
		lst = lst->next;
	}
	if (lst == NULL)
	{
		cmd->final_cmd = 1;
		if (pipe_before == 1 || cmd->pipe == 1)
			cmd->inside_pipe = 1;
		return (lst);
	}
	if (lst->content[0] == '|')
	{
		cmd->pipe = 1;
		cmd->inside_pipe = 1;
		lst = lst->next;
	}
	return (lst);
}
