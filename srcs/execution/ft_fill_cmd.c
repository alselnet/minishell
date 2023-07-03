/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 15:10:45 by orazafy           #+#    #+#             */
/*   Updated: 2023/07/03 15:21:56 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_cmd(t_cmd *cmd, t_token *lst)
{
	if (lst->type == 'R')
		ft_fill_cmd_for_type_r(cmd, lst);
	if (lst->type == 'C')
	{
		cmd->cmd_value = ft_merge_cmd(lst);
		if (cmd->cmd_value == NULL)
			ft_error(1);
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

void	ft_fill_cmd_for_type_r(t_cmd *cmd, t_token *lst)
{
	if (lst->content[0] == '<')
	{
		if (cmd->fd_in == -1)
			return ;
		if (cmd->fd_in != -2)
			close(cmd->fd_in);
		if (lst->content[1] == '<')
			cmd->fd_in = open(".hdoc.txt", O_RDONLY, 0500);
		else
			cmd->fd_in = open(lst->next->content, O_RDONLY, 0500);
		if (cmd->fd_in == -1)
			ft_error_no_such_file(lst->next->content);
	}
	ft_fill_cmd_for_type_r2(cmd, lst);
}

void	ft_fill_cmd_for_type_r2(t_cmd *cmd, t_token *lst)
{
	char	*outfile;

	outfile = lst->next->content;
	if (lst->content[0] == '>')
	{
		if (cmd->fd_out != -2)
			close(cmd->fd_out);
		if (lst->content[1] == '>')
			cmd->fd_out = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0664);
		else
			cmd->fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (cmd->fd_out == -1)
			ft_error(1);
	}
}

char	*ft_merge_cmd(t_token *lst)
{
	char	*result;

	result = ft_strdup(lst->content);
	if (result == NULL)
		ft_error(1);
	if (lst->next == NULL)
		return (result);
	lst = lst->next;
	while (lst != NULL && lst->content[0] != '|')
	{
		if (lst->type == 'A')
			result = ft_strjoin_free(result, " ");
		if (result == NULL)
			ft_error(1);
		if (lst->type == 'A')
			result = ft_strjoin_free(result, lst->content);
		if (result == NULL)
			ft_error(1);
		lst = lst->next;
	}
	return (result);
}

char	*ft_strjoin_free(char *str1, char *str2)
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	len1;
	ssize_t	len2;
	char	*dest;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	dest = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (str1[i])
	{
		dest[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
		dest[i++] = str2[j++];
	dest[i] = 0;
	free(str1);
	return (dest);
}
