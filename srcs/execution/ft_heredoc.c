/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 08:15:24 by aselnet           #+#    #+#             */
/*   Updated: 2023/06/29 09:14:24 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gnl(void)
{
	char	*buffer;

	buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
	if (!buffer)
		return (0);
	read(0, buffer, BUFFER_SIZE);
	return (buffer);
}

t_token	*has_heredoc(t_token *tklist_head)
{
	t_token *browse;

	browse = tklist_head;
	while (browse && browse->content[0] != '|')
	{
		if (browse->content[0] == '<' && browse->content[1] == '<')
			return (browse);
		browse = browse->next;
	}
	return (0);
}

void	fetch_heredoc(t_cmd *cmd, t_token *tklist_head)
{
	t_token	*redir;
	char	*line;

	if (cmd->fd_heredoc != -2)
	{
		cmd->fd_heredoc = -2;
		unlink(".hdoc.txt");
	}
	redir = has_heredoc(tklist_head);
	if (!redir)
		return ;
	cmd->fd_heredoc = open(".hdoc.txt", O_CREAT | O_WRONLY, 0664);
	if (cmd->fd_heredoc < 0)
		ft_error (1);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = gnl();
		if (!line)
			ft_error(1);
		if (ft_strncmp(redir->next->content,
			line, ft_strlen(redir->next->content) - 1) == 0)
			break ;
		write(cmd->fd_heredoc, line, BUFFER_SIZE);
		free(line);
	}
	close (cmd->fd_heredoc);
}
