/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orazafy <orazafy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 14:59:34 by orazafy           #+#    #+#             */
/*   Updated: 2023/06/21 16:07:09 by orazafy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_get_cmd(t_token *tklist_head, t_cmd *cmd)
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
	ft_fill_argc_argv(cmd);
	if (lst == NULL)
	{
		cmd->final_cmd = 1;
		return (lst);
	}
	if (lst->content[0] == '|')
	{
		cmd->pipe = 1;
		lst = lst->next;
	}
	return (lst);
}

void	ft_fill_argc_argv(t_cmd *cmd)
{
	if (cmd->has_cmd == 1)
	{
		ft_fill_argc(cmd);
		cmd->argv = ft_split(cmd->cmd_value, ' ');
		if (cmd->argv == NULL)
			ft_error(1);
	}
}

void	ft_fill_argc(t_cmd *cmd)
{
	char	*start;
	char	*str;

	str = cmd->cmd_value;
	while (*str)
	{
		while (*str && *str == ' ')
			str++;
		start = str;
		while (*str && *str != ' ')
			str++;
		if (str - start > 0)
			cmd->argc++;
		if (*str != 0)
			str++;
	}
}
