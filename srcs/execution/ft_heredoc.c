/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 08:15:24 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/04 14:13:07 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gnl(void)
{
	char	*buffer;

	buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
	if (!buffer)
		return (0);
	read(g_minishell.data_env.stdin, buffer, BUFFER_SIZE);
	return (buffer);
}

t_token	*has_heredoc(t_token **cursor)
{
	t_token	*browse;

	browse = *cursor;
	while (browse && browse->content[0] != '|')
	{
		if (browse->content[0] == '<' && browse->content[1] == '<')
		{
			*cursor = browse;
			return (browse);
		}
		browse = browse->next;
	}
	*cursor = browse;
	return (0);
}

void	unlink_heredoc(t_cmd *cmd)
{
	if (cmd->fd_heredoc != -2)
	{
		cmd->fd_heredoc = -2;
		unlink(".hdoc.txt");
	}
}

void	heredoc_process(t_cmd *cmd, t_token *redir)
{
	char	*line;

	while (1)
	{
		write(1, "heredoc> ", 9);
		line = gnl();
		if (!line)
			ft_error(1);
		if (*line == 0)
		{
			write(1, "\n", 1);
			free(line);
			return ;
		}
		if (ft_strncmp(redir->next->content,
				line, ft_strlen(redir->next->content) - 1) == 0)
		{
			free(line);
			return ;
		}
		write(cmd->fd_heredoc, line, BUFFER_SIZE);
		free(line);
	}
}

void	fetch_heredoc(t_cmd *cmd, t_token *tklist_head)
{
	t_token	*redir;
	t_token	*browse;

	browse = tklist_head;
	unlink_heredoc(cmd);
	redir = has_heredoc(&browse);
	if (!redir)
		return ;
	while (redir)
	{
		cmd->fd_heredoc = open(".hdoc.txt", O_CREAT | O_WRONLY, 0664);
		if (cmd->fd_heredoc < 0)
			ft_error(1);
		heredoc_process(cmd, redir);
		if (browse && browse->content[0] != '|')
		{
			browse = browse->next;
			redir = has_heredoc(&browse);
		}
		ft_close (&cmd->fd_heredoc);
	}
}
