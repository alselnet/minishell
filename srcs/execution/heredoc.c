/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 08:15:24 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/06 18:48:25 by aselnet          ###   ########.fr       */
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

t_token	*fetch_delim(t_token **cursor)
{
	t_token	*browse;

	browse = *cursor;
	while (browse && browse->content[0] != '|')
	{
		if (browse->content[0] == '<' && browse->content[1] == '<')
		{
			*cursor = browse;
			return (browse->next);
		}
		browse = browse->next;
	}
	*cursor = browse;
	return (0);
}

char	*process_line(char *line, t_token *delim, t_data_env *data_env)
{
	char *new_line;

	if (delim->delim_quote || !ft_isinbase('$', line)
		|| ft_isinbase(line[0], "\'"))
		return (line);
	new_line = expand_process(line, data_env);
	if (!new_line)
		return (0);
	return (new_line);
}

void	heredoc_process(t_cmd *cmd, t_data_env *data_env, t_token *delim)
{
	char	*line;
	char	*new_line;

	while (1)
	{
		write(1, "heredoc> ", 9);
		line = gnl();
		if (!line)
			return ;
		if (*line == 0)
		{
			write(1, "\n", 1);
			free(line);
			return ;
		}
		printf("line before processing\n%s\n", line);
		new_line = process_line(line, delim, data_env);
		printf("line after processing\n%s\n", new_line);
		if (!new_line)
			return ;
		if (ft_strncmp(delim->content,
				new_line, ft_strlen(delim->content) - 1) == 0)
		{
			free(new_line);
			return ;
		}
		write(cmd->fd_heredoc, new_line, BUFFER_SIZE);
		free (new_line);
	}
}

void	fetch_heredoc(t_cmd *cmd, t_token *tklist_head, t_data_env *data_env)
{
	t_token	*delim;
	t_token	*browse;

	browse = tklist_head;
	if (cmd->fd_heredoc != -2)
	{
		cmd->fd_heredoc = -2;
		unlink(".hdoc.txt");
	}
	delim = fetch_delim(&browse);
	if (!delim)
		return ;
	while (delim)
	{
		cmd->fd_heredoc = open(".hdoc.txt", O_CREAT | O_WRONLY, 0664);
		if (cmd->fd_heredoc < 0)
			ft_error(1);
		heredoc_process(cmd, data_env, delim);
		if (browse && browse->content[0] != '|')
		{
			browse = browse->next;
			delim = fetch_delim(&browse);
		}
		ft_close (&cmd->fd_heredoc);
	}
}
