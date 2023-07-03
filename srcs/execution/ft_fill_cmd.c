/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:10:45 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/03 16:35:48 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_cmd(t_cmd *cmd, t_token *lst)
{
	if (lst->type == 'R')
		ft_fill_cmd_for_type_r(cmd, lst);
	if (lst->type == 'C')
	{
		ft_fill_argc_argv(cmd, lst);
		cmd->has_cmd = 1;
	}
	if (lst->type == 'A')
	{
		if (cmd->first_arg_done != 1)
			cmd->first_arg = ft_strdup(lst->content);
		if (cmd->first_arg == NULL)
			ft_error(1);
		cmd->first_arg_done = 1;
	}
}

void	ft_fill_argc_argv(t_cmd *cmd, t_token *lst)
{
	ft_malloc_argv(cmd, lst);
	ft_split_cmd_option(cmd, lst);
	if (lst->next == NULL)
		return ;
	lst = lst->next;
	while (lst != NULL && lst->content[0] != '|')
	{
		if (lst->type == 'A')
			cmd->argv[cmd->argc++] = ft_strdup(lst->content);
		if (cmd->argv[cmd->argc - 1] == NULL)
			ft_error(1);
		lst = lst->next;
	}
}

void	ft_split_cmd_option(t_cmd *cmd, t_token *lst)
{
	int		space_pos;
	int		len_option;
	char	*content;

	content = lst->content;
	space_pos = ft_srch(' ', content);
	len_option = ft_strlen(content + space_pos + 1);
	if (space_pos != -1)
	{
		cmd->argv[cmd->argc++] = ft_substr(content, 0, space_pos);
		cmd->argv[cmd->argc++] = ft_substr(content, space_pos + 1, len_option);
		if (cmd->argv[cmd->argc - 1] == NULL
			|| cmd->argv[cmd->argc - 2] == NULL)
			ft_error(1);
	}
	else
		cmd->argv[cmd->argc++] = ft_strdup(content);
	if (cmd->argv[cmd->argc - 1] == NULL)
		ft_error(1);
}

void	ft_malloc_argv(t_cmd *cmd, t_token *lst)
{
	int	argc;

	argc = 1;
	if (ft_srch(' ', lst->content) != -1)
		argc++;
	while (lst != NULL && lst->content[0] != '|')
	{
		if (lst->type == 'A')
			argc++;
		lst = lst->next;
	}
	cmd->argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (cmd->argv == NULL)
		ft_error(1);
	cmd->argv[argc] = NULL;
}
